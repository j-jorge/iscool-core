/*
  Copyright 2018-present IsCool Entertainment

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#include "iscool/optional.h"
#include "iscool/optional.impl.tpp"
#include "iscool/net/message_channel.h"
#include "iscool/net/socket_stream.h"
#include "iscool/net/message/deserialize_message.h"
#include "iscool/net/message/serialize_message.h"
#include "iscool/schedule/manual_scheduler.h"
#include "iscool/schedule/setup.h"

#include <thread>

#include <gtest/gtest.h>

class iscool_scheduler_initializer
{
public:
    iscool_scheduler_initializer
    (iscool::schedule::delayed_call_delegate delegate)
    {
        iscool::schedule::initialize(std::move(delegate));
    }

    ~iscool_scheduler_initializer()
    {
        iscool::schedule::finalize();
    }
};

class message_channel_test:
    public ::testing::Test
{
public:
    message_channel_test();

    void server_send( const iscool::net::byte_array& bytes );
    void server_receive();

    void wait();

protected:
    iscool::net::byte_array _server_received_bytes;
    iscool::schedule::manual_scheduler _scheduler;

private:
    iscool_scheduler_initializer _scheduler_initializer;
    boost::asio::io_service _io_service;
    iscool::net::socket_stream _socket;
    iscool::optional< iscool::net::endpoint > _client_endpoint;
};

message_channel_test::message_channel_test()
    : _scheduler_initializer(_scheduler.get_delayed_call_delegate()),
      _socket( "127.0.0.1:32567", iscool::net::socket_mode::server{} )
{
    _socket.connect_to_received
        ([this](const iscool::net::endpoint& endpoint,
                iscool::net::byte_array bytes) -> void
            {
                _client_endpoint.emplace(endpoint);
                _server_received_bytes = std::move(bytes);
            });
}

void message_channel_test::server_send( const iscool::net::byte_array& bytes )
{
    _socket.send( *_client_endpoint, bytes );
}

void message_channel_test::server_receive()
{
    for (int i = 0; (i != 10) && !_client_endpoint; ++i)
        wait();

    EXPECT_TRUE(!!_client_endpoint);
}

void message_channel_test::wait()
{
    static constexpr std::chrono::milliseconds delay( 10 );
    std::this_thread::sleep_for( delay );

    _scheduler.update_interval( delay );
}

TEST_F( message_channel_test, constructor_sets_fields )
{
    iscool::net::socket_stream socket
        ( "127.0.0.1:32567", iscool::net::socket_mode::client{} );
    const iscool::net::xor_key key( { 0xa5, 0x5a } );
    const iscool::net::message_channel channel( socket, 1, 2, key );

    EXPECT_EQ( &socket, &channel.get_socket() );
    EXPECT_EQ( iscool::net::session_id( 1 ), channel.get_session_id() );
    EXPECT_EQ( iscool::net::channel_id( 2 ), channel.get_channel_id() );
    EXPECT_EQ( key, channel.get_obfuscation_key() );
}

TEST_F( message_channel_test, copy_constructor )
{
    iscool::net::socket_stream socket
        ( "127.0.0.1:32567", iscool::net::socket_mode::client{} );
    const iscool::net::xor_key key( { 0xa5, 0x5a } );
    const iscool::net::message_channel channel( socket, 2, 3, key );
    const iscool::net::message_channel copy( channel );

    EXPECT_EQ( &socket, &copy.get_socket() );
    EXPECT_EQ( channel.get_session_id(), copy.get_session_id() );
    EXPECT_EQ( channel.get_channel_id(), copy.get_channel_id() );
    EXPECT_EQ( channel.get_obfuscation_key(), copy.get_obfuscation_key() );
}

TEST_F( message_channel_test, set_session_and_channel_no_endpoint )
{
    iscool::net::socket_stream socket
        ( "127.0.0.1:32567", iscool::net::socket_mode::client{} );
    const iscool::net::session_id session( 4 );
    const iscool::net::channel_id channel( 5 );
    const iscool::net::xor_key key( { 0xa5, 0x5a } );
    const iscool::net::message_channel message_channel
        ( socket, session, channel, key );

    message_channel.send
        ( iscool::net::message( 12, iscool::net::byte_array() ) );

    server_receive();

    const iscool::net::message message_sent
        ( iscool::net::deserialize_message( _server_received_bytes, key ) );

    EXPECT_EQ( session, message_sent.get_session_id() );
    EXPECT_EQ( channel, message_sent.get_channel_id() );
}

TEST_F( message_channel_test, set_session_and_channel_with_endpoint )
{
    iscool::net::socket_stream socket
        ( "127.0.0.1:32567", iscool::net::socket_mode::client{} );
    const iscool::net::session_id session( 6 );
    const iscool::net::channel_id channel( 7 );
    const iscool::net::xor_key key( { 0xa5, 0x5a } );
    const iscool::net::message_channel message_channel
        ( socket, session, channel, key );
    const iscool::net::endpoint endpoint
        ( boost::asio::ip::address::from_string( "127.0.0.1" ), 32567 );

    message_channel.send
        ( endpoint, iscool::net::message( 24, iscool::net::byte_array() ) );

    server_receive();

    const iscool::net::message message_sent
        ( iscool::net::deserialize_message( _server_received_bytes, key ) );

    EXPECT_EQ( session, message_sent.get_session_id() );
    EXPECT_EQ( channel, message_sent.get_channel_id() );
}

TEST_F( message_channel_test, dispatch_message_matching_session_and_channel )
{
    iscool::net::socket_stream socket
        ( "127.0.0.1:32567", iscool::net::socket_mode::client{} );
    const iscool::net::session_id session( 8 );
    const iscool::net::channel_id channel( 9 );
    const iscool::net::xor_key key( { 0xa5, 0x5a } );
    const iscool::net::message_channel message_channel
        ( socket, session, channel, key );

    message_channel.send
        ( iscool::net::message( 0, iscool::net::byte_array() ) );
    server_receive();

    bool message_sent( false );
    const auto message_handler
        ( [ &message_sent, session, channel ]
          ( const iscool::net::endpoint& endpoint,
            const iscool::net::message& m ) -> void
          {
              EXPECT_EQ( session, m.get_session_id() );
              EXPECT_EQ( channel, m.get_channel_id() );
              message_sent = true;
          } );

    message_channel.connect_to_message( message_handler );

    iscool::net::message message( 0, iscool::net::byte_array() );
    message.set_session_id( session );
    message.set_channel_id( channel );

    server_send( iscool::net::serialize_message( message, key ) );
    wait();

    EXPECT_TRUE( message_sent );
}

TEST_F( message_channel_test, ignore_message_matching_non_matching_session )
{
    iscool::net::socket_stream socket
        ( "127.0.0.1:32567", iscool::net::socket_mode::client{} );
    const iscool::net::session_id session( 8 );
    const iscool::net::channel_id channel( 9 );
    const iscool::net::xor_key key( { 0xa5, 0x5a } );
    const iscool::net::message_channel message_channel
        ( socket, session, channel, key );

    message_channel.send
        ( iscool::net::message( 0, iscool::net::byte_array() ) );
    server_receive();

    bool message_sent( false );
    const auto message_handler
        ( [ &message_sent ]
          ( const iscool::net::endpoint& endpoint,
            const iscool::net::message& m ) -> void
          {
              message_sent = true;
          } );

    message_channel.connect_to_message( message_handler );

    iscool::net::message message( 0, iscool::net::byte_array() );
    message.set_session_id( session * 2 );
    message.set_channel_id( channel );

    server_send( iscool::net::serialize_message( message, key ) );
    wait();

    EXPECT_FALSE( message_sent );
}

TEST_F( message_channel_test, ignore_message_matching_non_matching_channel )
{
    iscool::net::socket_stream socket
        ( "127.0.0.1:32567", iscool::net::socket_mode::client{} );
    const iscool::net::session_id session( 8 );
    const iscool::net::channel_id channel( 9 );
    const iscool::net::xor_key key( { 0xa5, 0x5a } );
    const iscool::net::message_channel message_channel
        ( socket, session, channel, key );

    message_channel.send
        ( iscool::net::message( 0, iscool::net::byte_array() ) );
    server_receive();

    bool message_sent( false );
    const auto message_handler
        ( [ &message_sent ]
          ( const iscool::net::endpoint& endpoint,
            const iscool::net::message& m ) -> void
          {
              message_sent = true;
          } );

    message_channel.connect_to_message( message_handler );

    iscool::net::message message( 0, iscool::net::byte_array() );
    message.set_session_id( session );
    message.set_channel_id( channel * 2 );

    server_send( iscool::net::serialize_message( message, key ) );
    wait();

    EXPECT_FALSE( message_sent );
}

TEST_F( message_channel_test, serialization_xor )
{
    iscool::net::socket_stream socket
        ( "127.0.0.1:32567", iscool::net::socket_mode::client{} );
    const iscool::net::session_id session( 12 );
    const iscool::net::channel_id channel( 24 );
    const iscool::net::xor_key key( { 0xa5, 0x5a } );
    const iscool::net::message_channel message_channel
        ( socket, session, channel, key );

    iscool::net::byte_array content;
    content.append<std::uint8_t>( 0xf0 );
    content.append<std::uint8_t>( 0xff );
    content.append<std::uint8_t>( 0x0f );
    content.append<std::uint8_t>( 0xaa );
    content.append<std::uint8_t>( 0x0f );

    const iscool::net::message_type type( 72 );
    const iscool::net::message reference( type, content );

    message_channel.send( reference );
    server_receive();

    const iscool::net::message message_sent
        ( iscool::net::deserialize_message( _server_received_bytes, { 0 } ) );

    EXPECT_EQ( session, message_sent.get_session_id() );
    EXPECT_EQ( channel, message_sent.get_channel_id() );
    EXPECT_EQ( type, message_sent.get_type() );

    const iscool::net::byte_array crypted( message_sent.get_content() );

    ASSERT_EQ( content.size(), crypted.size() );
    EXPECT_EQ( std::uint8_t( 0xf0 ) ^ std::uint8_t( 0xa5 ), crypted[ 0 ] );
    EXPECT_EQ( std::uint8_t( 0xff ) ^ std::uint8_t( 0x5a ), crypted[ 1 ] );
    EXPECT_EQ( std::uint8_t( 0x0f ) ^ std::uint8_t( 0xa5 ), crypted[ 2 ] );
    EXPECT_EQ( std::uint8_t( 0xaa ) ^ std::uint8_t( 0x5a ), crypted[ 3 ] );
    EXPECT_EQ( std::uint8_t( 0x0f ) ^ std::uint8_t( 0xa5 ), crypted[ 4 ] );

    iscool::net::message message_received;

    const auto message_handler
        ( [ &message_received ]
          ( const iscool::net::endpoint& endpoint,
            const iscool::net::message& m ) -> void
          {
              message_received = m;
          } );

    message_channel.connect_to_message( message_handler );

    server_send( iscool::net::serialize_message( message_sent, { 0 } ) );
    wait();

    EXPECT_EQ( session, message_received.get_session_id() );
    EXPECT_EQ( channel, message_received.get_channel_id() );
    EXPECT_EQ( type, message_received.get_type() );

    const iscool::net::byte_array decrypted( message_received.get_content() );

    ASSERT_EQ( content.size(), decrypted.size() );
    EXPECT_EQ( content[ 0 ], decrypted[ 0 ] );
    EXPECT_EQ( content[ 1 ], decrypted[ 1 ] );
    EXPECT_EQ( content[ 2 ], decrypted[ 2 ] );
    EXPECT_EQ( content[ 3 ], decrypted[ 3 ] );
    EXPECT_EQ( content[ 4 ], decrypted[ 4 ] );
}
