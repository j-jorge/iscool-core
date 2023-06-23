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
#include "iscool/net/byte_array_bit_reader.h"

#include "iscool/net/byte_array.h"
#include "iscool/net/byte_array_reader.h"

#include <gtest/gtest.h>

TEST(iscool_net_byte_array_bit_reader, get)
{
  const std::vector<std::uint8_t> content({ 0xbb, 0xa0 });
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);
  iscool::net::byte_array_bit_reader bit_reader(reader);

  EXPECT_EQ(2, bit_reader.get(2));
  EXPECT_EQ(3, bit_reader.get(2));
  EXPECT_EQ(5, bit_reader.get(3));
  EXPECT_EQ(26, bit_reader.get(5));
}

TEST(iscool_net_byte_array_bit_reader, get_large)
{
  const std::vector<std::uint8_t> content({ 0xa6, 0x96, 0xab, 0x00 });
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);
  iscool::net::byte_array_bit_reader bit_reader(reader);

  EXPECT_EQ(2, bit_reader.get(2));
  EXPECT_EQ(2469, bit_reader.get_large<std::uint16_t>(12));
  EXPECT_EQ(1366, bit_reader.get_large<std::uint16_t>(11));
}
