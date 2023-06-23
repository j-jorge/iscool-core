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
#include "iscool/net/message/raw_message.h"

// #include "iscool/net/byte_array_reader.h"
// #include "iscool/net/message/deserialize_message.h"

// #include
// "iscool/net/byte_array_serialization/byte_array_array_serialization.h"
// #include "iscool/net/message/serialize_message.h"

#include <gtest/gtest.h>

TEST(raw_message_test, getters)
{
  using array_type = std::array<std::uint32_t, 3>;

  DECLARE_RAW_MESSAGE(message_type, 123,
                      ((std::uint32_t)(some_int))((array_type)(some_array)));

  const message_type message(24, { 1, 3, 2 });

  EXPECT_EQ(123, message.get_type());
  EXPECT_EQ(24, message.get_some_int());
  EXPECT_EQ(1, message.get_some_array()[0]);
  EXPECT_EQ(3, message.get_some_array()[1]);
  EXPECT_EQ(2, message.get_some_array()[2]);

  const array_type& array = message.get_some_array();
  EXPECT_EQ(&array, &message.get_some_array());
}

TEST(raw_message_test, serialization)
{
  using array_type = std::array<std::uint32_t, 3>;

  DECLARE_RAW_MESSAGE(message_type, 123,
                      ((std::uint32_t)(some_int))((array_type)(some_array)));

  const message_type message(24, { 1, 3, 2 });

  const iscool::net::message wrapped = message.build_message();

  EXPECT_EQ(123, wrapped.get_type());
  EXPECT_EQ(0, wrapped.get_session_id());
  EXPECT_EQ(0, wrapped.get_channel_id());

  const message_type deserialized(wrapped.get_content());

  EXPECT_EQ(123, deserialized.get_type());
  EXPECT_EQ(24, deserialized.get_some_int());
  EXPECT_EQ(1, deserialized.get_some_array()[0]);
  EXPECT_EQ(3, deserialized.get_some_array()[1]);
  EXPECT_EQ(2, deserialized.get_some_array()[2]);

  const array_type& array = deserialized.get_some_array();
  EXPECT_EQ(&array, &deserialized.get_some_array());
  EXPECT_NE(&array, &message.get_some_array());
}
