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
#include <iscool/net/byte_array_serialization/byte_array_serialization.hpp>

TEST(byte_array_serialization_test, simple_values)
{
  iscool::net::byte_array output;
  output << std::uint8_t(0x01) << std::uint16_t(0x0123)
         << std::uint32_t(0x01234567) << std::uint64_t(0x0123456789abcdef);

  iscool::net::byte_array_reader input(output);
  std::uint8_t a;
  input >> a;
  ASSERT_EQ(std::uint8_t(0x01), a);

  std::uint16_t b;
  input >> b;
  ASSERT_EQ(std::uint16_t(0x0123), b);

  std::uint32_t c;
  input >> c;
  ASSERT_EQ(std::uint32_t(0x01234567), c);

  std::uint64_t d;
  input >> d;
  ASSERT_EQ(std::uint64_t(0x0123456789abcdef), d);
}
