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
#include <gtest/gtest.h>

#include "iscool/net/byte_array.h"
#include "iscool/net/byte_array_reader.h"
#include "iscool/net/byte_array_serialization/byte_array_tuple_serialization.h"

TEST(byte_array_tuple_serialization_test, empty_tuple)
{
  typedef std::tuple<> tuple_type;

  iscool::net::byte_array output;
  output << tuple_type();

  iscool::net::byte_array_reader input(output);
  tuple_type v;
  input >> v;
}

TEST(byte_array_tuple_serialization_test, non_empty)
{
  typedef std::tuple<std::uint32_t, std::uint8_t> tuple_type;

  const tuple_type reference{ 0x01234567, 0x01 };

  iscool::net::byte_array output;
  output << reference;

  iscool::net::byte_array_reader input(output);
  tuple_type t;
  input >> t;

  EXPECT_EQ(reference, t);
}

TEST(byte_array_tuple_serialization_test, overwrites)
{
  typedef std::tuple<std::uint32_t, std::uint8_t> tuple_type;

  const tuple_type reference{ 0x01234567, 0x01 };

  iscool::net::byte_array output;
  output << reference;

  iscool::net::byte_array_reader input(output);
  tuple_type t{ 0x76543210, 0x10 };
  input >> t;

  EXPECT_EQ(reference, t);
}

TEST(byte_array_tuple_serialization_test, between_values)
{
  typedef std::tuple<std::uint32_t, std::uint8_t> tuple_type;

  const tuple_type reference{ 0x01234567, 0x01 };

  iscool::net::byte_array output;
  output << std::uint16_t(0x0123) << reference << std::uint32_t(0x01234567);

  iscool::net::byte_array_reader input(output);
  std::uint16_t a;
  tuple_type t;
  std::uint32_t b;
  input >> a >> t >> b;

  EXPECT_EQ(std::uint16_t(0x0123), a);
  EXPECT_EQ(reference, t);
  EXPECT_EQ(std::uint32_t(0x01234567), b);
}
