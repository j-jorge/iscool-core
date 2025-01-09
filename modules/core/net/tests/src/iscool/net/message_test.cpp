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
#include <iscool/net/byte_array_reader.hpp>
#include <iscool/net/message/deserialize_message.hpp>
#include <iscool/net/message/message.hpp>
#include <iscool/net/message/serialize_message.hpp>

#include <gtest/gtest.h>

TEST(message_test, constructor_sets_fields)
{
  iscool::net::byte_array content;
  content.append<std::uint8_t>(3);
  content.append<std::uint8_t>(1);
  content.append<std::uint8_t>(2);

  const iscool::net::message message(6, content);

  EXPECT_EQ(6, message.get_type());

  const std::span<const std::uint8_t> message_content(message.get_content());
  ASSERT_EQ(content.size(), message_content.size());

  for (std::size_t i(0); i != content.size(); ++i)
    EXPECT_EQ(content[i], message_content[i])
        << "content's byte #" << i << " is different";
}

TEST(message_test, default_field_values)
{
  iscool::net::byte_array content;
  const iscool::net::message message(12, content);

  EXPECT_EQ(0ull, message.get_session_id());
  EXPECT_EQ(0ull, message.get_channel_id());
}

TEST(message_test, serialization)
{
  iscool::net::byte_array content;
  content.append<std::uint8_t>(3);
  content.append<std::uint8_t>(1);
  content.append<std::uint8_t>(2);

  iscool::net::message reference(12, content);
  reference.set_session_id(12);
  reference.set_channel_id(24);

  iscool::net::byte_array serialized_bytes =
      iscool::net::serialize_message(reference);
  iscool::net::message serialized;
  iscool::net::deserialize_message(serialized, serialized_bytes);

  EXPECT_EQ(reference.get_type(), serialized.get_type());
  EXPECT_EQ(reference.get_session_id(), serialized.get_session_id());
  EXPECT_EQ(reference.get_channel_id(), serialized.get_channel_id());

  const std::span<const std::uint8_t> serialized_content(
      serialized.get_content());
  ASSERT_EQ(content.size(), serialized_content.size());

  for (std::size_t i(0); i != content.size(); ++i)
    EXPECT_EQ(content[i], serialized_content[i])
        << "content's byte #" << i << " is different";
}

TEST(message_test, content_header)
{
  iscool::net::byte_array content;
  content.append<std::uint8_t>(1);
  content.append<std::uint8_t>(1);

  iscool::net::message reference(15, content);
  reference.set_session_id(16);
  reference.set_channel_id(32);

  const iscool::net::byte_array raw_message(
      iscool::net::serialize_message(reference));

  const std::size_t expected_size(
      sizeof(iscool::net::message_type) + sizeof(std::uint16_t)
      + sizeof(iscool::net::session_id) + sizeof(iscool::net::channel_id)
      + content.size());
  ASSERT_EQ(expected_size, raw_message.size());

  iscool::net::byte_array_reader reader(raw_message);

  EXPECT_EQ(reference.get_type(), reader.get<iscool::net::message_type>());
  EXPECT_EQ(expected_size, reader.get<std::uint16_t>());
  EXPECT_EQ(reference.get_session_id(), reader.get<iscool::net::session_id>());
  EXPECT_EQ(reference.get_channel_id(), reader.get<iscool::net::channel_id>());

  for (std::size_t i(0); i != content.size(); ++i)
    EXPECT_EQ(content[i], reader.get<std::uint8_t>())
        << "Content's byte #" << i << " is different";
}

TEST(message_test, serialization_xor)
{
  iscool::net::byte_array content;
  content.append<std::uint8_t>(0xf0);
  content.append<std::uint8_t>(0xff);
  content.append<std::uint8_t>(0x0f);
  content.append<std::uint8_t>(0xaa);
  content.append<std::uint8_t>(0x0f);

  iscool::net::message reference(72, content);
  reference.set_session_id(12);
  reference.set_channel_id(24);

  const iscool::net::xor_key key({ 0xa5, 0x5a });

  iscool::net::byte_array serialized(
      iscool::net::serialize_message(reference, key));

  iscool::net::message message;
  iscool::net::deserialize_message(message, serialized);
  const iscool::net::byte_array crypted(message.get_content().begin(),
                                        message.get_content().end());

  ASSERT_EQ(content.size(), crypted.size());
  EXPECT_EQ(std::uint8_t(0xf0) ^ std::uint8_t(0xa5), crypted[0]);
  EXPECT_EQ(std::uint8_t(0xff) ^ std::uint8_t(0x5a), crypted[1]);
  EXPECT_EQ(std::uint8_t(0x0f) ^ std::uint8_t(0xa5), crypted[2]);
  EXPECT_EQ(std::uint8_t(0xaa) ^ std::uint8_t(0x5a), crypted[3]);
  EXPECT_EQ(std::uint8_t(0x0f) ^ std::uint8_t(0xa5), crypted[4]);

  iscool::net::message deserialized;
  iscool::net::deserialize_message(deserialized, serialized, key);

  EXPECT_EQ(iscool::net::message_type(72), deserialized.get_type());
  EXPECT_EQ(iscool::net::session_id(12), deserialized.get_session_id());
  EXPECT_EQ(iscool::net::channel_id(24), deserialized.get_channel_id());

  const iscool::net::byte_array decrypted(deserialized.get_content().begin(),
                                          deserialized.get_content().end());

  ASSERT_EQ(content.size(), decrypted.size());

  for (std::size_t i(0); i != content.size(); ++i)
    EXPECT_EQ(content[i], decrypted[i])
        << "content's byte #" << i << " is different";
}

TEST(message_test, serialization_explicit_session_and_channel)
{
  iscool::net::byte_array content;
  content.append<std::uint8_t>(0x0f);
  content.append<std::uint8_t>(0xff);
  content.append<std::uint8_t>(0x0f);
  content.append<std::uint8_t>(0xaa);
  content.append<std::uint8_t>(0xf0);

  iscool::net::message reference(72, content);
  reference.set_session_id(12);
  reference.set_channel_id(24);

  const iscool::net::xor_key key({ 0xa5, 0x5a });

  iscool::net::byte_array serialized(
      iscool::net::serialize_message(reference, 34, 92, key));

  iscool::net::message deserialized;
  iscool::net::deserialize_message(deserialized, serialized, key);

  EXPECT_EQ(iscool::net::message_type(72), deserialized.get_type());
  EXPECT_EQ(iscool::net::session_id(34), deserialized.get_session_id());
  EXPECT_EQ(iscool::net::channel_id(92), deserialized.get_channel_id());
}
