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

#include <iscool/net/byte_array.hpp>
#include <iscool/net/byte_array_reader.hpp>

TEST(byte_array_enum_serialization_test, enum)
{
  // Serialization in a byte array only supports signed types.
  enum enum_type : std::uint8_t
  {
    a,
    b = 12,
    c
  };

  iscool::net::byte_array output;
  output << enum_type::c << enum_type::a << enum_type::b;

  iscool::net::byte_array_reader input(output);
  enum_type v;
  input >> v;
  EXPECT_EQ(enum_type::c, v);

  input >> v;
  EXPECT_EQ(enum_type::a, v);

  input >> v;
  EXPECT_EQ(enum_type::b, v);
}

TEST(byte_array_enum_serialization_test, enum_class)
{
  // Serialization in a byte array only supports signed types.
  enum class enum_type : std::uint16_t
  {
    a,
    b = 12,
    c
  };

  iscool::net::byte_array output;
  output << enum_type::c << enum_type::a << enum_type::b;

  iscool::net::byte_array_reader input(output);
  enum_type v;
  input >> v;
  EXPECT_EQ(enum_type::c, v);

  input >> v;
  EXPECT_EQ(enum_type::a, v);

  input >> v;
  EXPECT_EQ(enum_type::b, v);
}
