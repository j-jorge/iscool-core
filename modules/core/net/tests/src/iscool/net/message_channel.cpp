// SPDX-License-Identifier: Apache-2.0
#include <iscool/net/message/deserialize_message.hpp>
#include <iscool/net/message/serialize_message.hpp>
#include <iscool/net/message_channel.hpp>
#include <iscool/net/message_stream.hpp>
#include <iscool/net/socket_stream.hpp>
#include <iscool/optional.hpp>
#include <iscool/optional.impl.tpp>
#include <iscool/schedule/manual_scheduler.hpp>
#include <iscool/schedule/setup.hpp>

#include <thread>

#include <gtest/gtest.h>

class message_channel_test : public ::testing::Test
{
public:
  message_channel_test();

  void server_send(const iscool::net::byte_array& bytes);
  void server_receive();

  void wait();

protected:
  iscool::net::byte_array _server_received_bytes;
  iscool::schedule::manual_scheduler _scheduler;
  iscool::schedule::scoped_scheduler_delegate _scheduler_initializer;
  iscool::net::socket_stream _socket;

private:
  iscool::optional<iscool::net::endpoint> _client_endpoint;
};

message_channel_test::message_channel_test()
  : _scheduler_initializer(_scheduler.get_delayed_call_delegate())
  , _socket("127.0.0.1:32567", iscool::net::socket_mode::server{})
{
  _socket.connect_to_received(
      [this](const iscool::net::endpoint& endpoint,
             iscool::net::byte_array bytes) -> void
      {
        _client_endpoint.emplace(endpoint);
        _server_received_bytes = std::move(bytes);
      });
}

void message_channel_test::server_send(const iscool::net::byte_array& bytes)
{
  _socket.send(*_client_endpoint, bytes);
}

void message_channel_test::server_receive()
{
  for (int i = 0; (i != 10) && !_client_endpoint; ++i)
    wait();

  EXPECT_TRUE(!!_client_endpoint);
}

void message_channel_test::wait()
{
  static constexpr std::chrono::milliseconds delay(10);
  std::this_thread::sleep_for(delay);

  _scheduler.update_interval(delay);
}

TEST_F(message_channel_test, set_session_and_channel_no_endpoint)
{
  iscool::net::socket_stream socket("127.0.0.1:32567",
                                    iscool::net::socket_mode::client{});
  const iscool::net::session_id session(4);
  const iscool::net::channel_id channel(5);
  const iscool::net::xor_key key({ 0xa5, 0x5a });
  const iscool::net::message_stream stream(socket, key);
  const iscool::net::message_channel message_channel(stream, session, channel);

  message_channel.send(iscool::net::message(12, iscool::net::byte_array()));

  server_receive();

  iscool::net::message message_sent;
  iscool::net::deserialize_message(message_sent, _server_received_bytes, key);

  EXPECT_EQ(session, message_sent.get_session_id());
  EXPECT_EQ(channel, message_sent.get_channel_id());
}

TEST_F(message_channel_test, set_session_and_channel_with_endpoint)
{
  iscool::net::socket_stream socket("127.0.0.1:32567",
                                    iscool::net::socket_mode::client{});
  const iscool::net::session_id session(6);
  const iscool::net::channel_id channel(7);
  const iscool::net::xor_key key({ 0xa5, 0x5a });
  const iscool::net::message_stream stream(socket, key);
  const iscool::net::message_channel message_channel(stream, session, channel);
  const iscool::net::endpoint endpoint(
      boost::asio::ip::address::from_string("127.0.0.1"), 32567);

  message_channel.send(endpoint,
                       iscool::net::message(24, iscool::net::byte_array()));

  server_receive();

  iscool::net::message message_sent;
  iscool::net::deserialize_message(message_sent, _server_received_bytes, key);

  EXPECT_EQ(session, message_sent.get_session_id());
  EXPECT_EQ(channel, message_sent.get_channel_id());
}

TEST_F(message_channel_test, dispatch_message_matching_session_and_channel)
{
  iscool::net::socket_stream socket("127.0.0.1:32567",
                                    iscool::net::socket_mode::client{});
  const iscool::net::session_id session(8);
  const iscool::net::channel_id channel(9);
  const iscool::net::xor_key key({ 0xa5, 0x5a });
  const iscool::net::message_stream stream(socket, key);
  const iscool::net::message_channel message_channel(stream, session, channel);

  message_channel.send(iscool::net::message(0, iscool::net::byte_array()));
  server_receive();

  bool message_sent(false);
  const auto message_handler(
      [&message_sent, session, channel](const iscool::net::endpoint& endpoint,
                                        const iscool::net::message& m) -> void
      {
        EXPECT_EQ(session, m.get_session_id());
        EXPECT_EQ(channel, m.get_channel_id());
        message_sent = true;
      });

  message_channel.connect_to_message(message_handler);

  iscool::net::message message(0, iscool::net::byte_array());
  message.set_session_id(session);
  message.set_channel_id(channel);

  const iscool::net::byte_array serialized =
      iscool::net::serialize_message(message, key);
  server_send(serialized);
  wait();

  EXPECT_TRUE(message_sent);

  EXPECT_EQ(serialized.size(), socket.sent_bytes());
  EXPECT_EQ(serialized.size(), _socket.received_bytes());
}

TEST_F(message_channel_test, ignore_message_matching_non_matching_session)
{
  iscool::net::socket_stream socket("127.0.0.1:32567",
                                    iscool::net::socket_mode::client{});
  const iscool::net::session_id session(8);
  const iscool::net::channel_id channel(9);
  const iscool::net::xor_key key({ 0xa5, 0x5a });
  const iscool::net::message_stream stream(socket, key);
  const iscool::net::message_channel message_channel(stream, session, channel);

  message_channel.send(iscool::net::message(0, iscool::net::byte_array()));
  server_receive();

  bool message_sent(false);
  const auto message_handler(
      [&message_sent](const iscool::net::endpoint& endpoint,
                      const iscool::net::message& m) -> void
      {
        message_sent = true;
      });

  message_channel.connect_to_message(message_handler);

  iscool::net::message message(0, iscool::net::byte_array());
  message.set_session_id(session * 2);
  message.set_channel_id(channel);

  const iscool::net::byte_array serialized =
      iscool::net::serialize_message(message, key);
  server_send(serialized);
  wait();

  EXPECT_FALSE(message_sent);

  EXPECT_EQ(serialized.size(), socket.sent_bytes());
  EXPECT_EQ(serialized.size(), _socket.received_bytes());
}

TEST_F(message_channel_test, ignore_message_matching_non_matching_channel)
{
  iscool::net::socket_stream socket("127.0.0.1:32567",
                                    iscool::net::socket_mode::client{});
  const iscool::net::session_id session(8);
  const iscool::net::channel_id channel(9);
  const iscool::net::xor_key key({ 0xa5, 0x5a });
  const iscool::net::message_stream stream(socket, key);
  const iscool::net::message_channel message_channel(stream, session, channel);

  message_channel.send(iscool::net::message(0, iscool::net::byte_array()));
  server_receive();

  bool message_sent(false);
  const auto message_handler(
      [&message_sent](const iscool::net::endpoint& endpoint,
                      const iscool::net::message& m) -> void
      {
        message_sent = true;
      });

  message_channel.connect_to_message(message_handler);

  iscool::net::message message(0, iscool::net::byte_array());
  message.set_session_id(session);
  message.set_channel_id(channel * 2);

  const iscool::net::byte_array serialized =
      iscool::net::serialize_message(message, key);
  server_send(serialized);
  wait();

  EXPECT_FALSE(message_sent);

  EXPECT_EQ(serialized.size(), socket.sent_bytes());
  EXPECT_EQ(serialized.size(), _socket.received_bytes());
}

TEST_F(message_channel_test, serialization_xor)
{
  iscool::net::socket_stream socket("127.0.0.1:32567",
                                    iscool::net::socket_mode::client{});
  const iscool::net::session_id session(12);
  const iscool::net::channel_id channel(24);
  const iscool::net::xor_key key({ 0xa5, 0x5a });
  const iscool::net::message_stream stream(socket, key);
  const iscool::net::message_channel message_channel(stream, session, channel);

  iscool::net::byte_array content;
  content.append<std::uint8_t>(0xf0);
  content.append<std::uint8_t>(0xff);
  content.append<std::uint8_t>(0x0f);
  content.append<std::uint8_t>(0xaa);
  content.append<std::uint8_t>(0x0f);

  const iscool::net::message_type type(72);
  const iscool::net::message reference(type, content);

  message_channel.send(reference);
  server_receive();

  iscool::net::message message_sent;
  iscool::net::deserialize_message(message_sent, _server_received_bytes,
                                   { 0 });

  EXPECT_EQ(session, message_sent.get_session_id());
  EXPECT_EQ(channel, message_sent.get_channel_id());
  EXPECT_EQ(type, message_sent.get_type());

  const iscool::net::byte_array crypted(message_sent.get_content().begin(),
                                        message_sent.get_content().end());

  ASSERT_EQ(content.size(), crypted.size());
  EXPECT_EQ(std::uint8_t(0xf0) ^ std::uint8_t(0xa5), crypted[0]);
  EXPECT_EQ(std::uint8_t(0xff) ^ std::uint8_t(0x5a), crypted[1]);
  EXPECT_EQ(std::uint8_t(0x0f) ^ std::uint8_t(0xa5), crypted[2]);
  EXPECT_EQ(std::uint8_t(0xaa) ^ std::uint8_t(0x5a), crypted[3]);
  EXPECT_EQ(std::uint8_t(0x0f) ^ std::uint8_t(0xa5), crypted[4]);

  iscool::net::message message_received;

  const auto message_handler(
      [&message_received](const iscool::net::endpoint& endpoint,
                          const iscool::net::message& m) -> void
      {
        message_received = m;
      });

  message_channel.connect_to_message(message_handler);

  server_send(iscool::net::serialize_message(message_sent, { 0 }));
  wait();

  EXPECT_EQ(session, message_received.get_session_id());
  EXPECT_EQ(channel, message_received.get_channel_id());
  EXPECT_EQ(type, message_received.get_type());

  const iscool::net::byte_array decrypted(
      message_received.get_content().begin(),
      message_received.get_content().end());

  ASSERT_EQ(content.size(), decrypted.size());
  EXPECT_EQ(content[0], decrypted[0]);
  EXPECT_EQ(content[1], decrypted[1]);
  EXPECT_EQ(content[2], decrypted[2]);
  EXPECT_EQ(content[3], decrypted[3]);
  EXPECT_EQ(content[4], decrypted[4]);
}
