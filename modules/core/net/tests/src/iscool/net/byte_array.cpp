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
#include <iscool/net/byte_array.hpp>

#include <type_traits>

#include <gtest/gtest.h>

TEST(byte_array_test, movable)
{
  EXPECT_TRUE(std::is_move_constructible<iscool::net::byte_array>::value);
  EXPECT_TRUE(std::is_move_assignable<iscool::net::byte_array>::value);
}

TEST(byte_array_test, default_is_empty)
{
  iscool::net::byte_array array;
  EXPECT_EQ(0ull, array.size());
}

TEST(byte_array_test, inserted_byte_adds_one_byte)
{
  const std::uint8_t byte(73);

  iscool::net::byte_array array;
  array.append(byte);

  EXPECT_EQ(1ull, array.size());
  EXPECT_EQ(byte, array[0]);
}

TEST(byte_array_test, append_appends_to_end)
{
  const std::uint8_t first_byte(73);
  const std::uint8_t second_byte(24);

  iscool::net::byte_array array;
  array.append(first_byte);
  array.append(second_byte);

  EXPECT_EQ(2ull, array.size());
  EXPECT_EQ(first_byte, array[0]);
  EXPECT_EQ(second_byte, array[1]);
}

TEST(byte_array_test, appends_big_endian16)
{
  const std::uint16_t bytes(0x0102);

  iscool::net::byte_array array;
  array.append(bytes);

  EXPECT_EQ(2ull, array.size());
  EXPECT_EQ(0x01, array[0]);
  EXPECT_EQ(0x02, array[1]);
}

TEST(byte_array_test, appends_big_endian32)
{
  const std::uint32_t bytes(0x01020304);

  iscool::net::byte_array array;
  array.append(bytes);

  EXPECT_EQ(4ull, array.size());
  EXPECT_EQ(0x01, array[0]);
  EXPECT_EQ(0x02, array[1]);
  EXPECT_EQ(0x03, array[2]);
  EXPECT_EQ(0x04, array[3]);
}

TEST(byte_array_test, appends_big_endian64)
{
  const std::uint64_t bytes(0x0102030405060708);

  iscool::net::byte_array array;
  array.append(bytes);

  EXPECT_EQ(8ull, array.size());
  EXPECT_EQ(0x01, array[0]);
  EXPECT_EQ(0x02, array[1]);
  EXPECT_EQ(0x03, array[2]);
  EXPECT_EQ(0x04, array[3]);
  EXPECT_EQ(0x05, array[4]);
  EXPECT_EQ(0x06, array[5]);
  EXPECT_EQ(0x07, array[6]);
  EXPECT_EQ(0x08, array[7]);
}

TEST(byte_array_test, begin_end_order)
{
  const std::vector<std::uint8_t> bytes{ 1, 2, 3 };

  iscool::net::byte_array array;

  for (std::uint8_t byte : bytes)
    array.append(byte);

  EXPECT_EQ(bytes, std::vector<std::uint8_t>(array.begin(), array.end()));
}

TEST(byte_array_test, constructor_from_range)
{
  const std::vector<std::uint8_t> bytes{ 1, 2, 3 };

  iscool::net::byte_array array(bytes.begin(), bytes.end());

  EXPECT_EQ(bytes, std::vector<std::uint8_t>(array.begin(), array.end()));
}

TEST(byte_array_test, constructor_from_range_large)
{
  const std::vector<std::uint16_t> bytes{ 0x0102, 0x0304, 0x0506 };
  const std::vector<std::uint8_t> expected{ 1, 2, 3, 4, 5, 6 };

  const iscool::net::byte_array array(bytes.begin(), bytes.end());

  EXPECT_EQ(expected, std::vector<std::uint8_t>(array.begin(), array.end()));
}

TEST(byte_array_test, append_empty_to_empty)
{
  iscool::net::byte_array first_array;
  iscool::net::byte_array second_array;

  first_array.append(second_array);
  EXPECT_EQ(0ull, first_array.size());
}

TEST(byte_array_test, append_empty_to_non_empty)
{
  const std::vector<std::uint8_t> bytes{ 1, 2, 3 };
  iscool::net::byte_array array(bytes.begin(), bytes.end());

  array.append(iscool::net::byte_array());
  EXPECT_EQ(bytes, std::vector<std::uint8_t>(array.begin(), array.end()));
}

TEST(byte_array_test, append_non_empty_to_empty)
{
  const std::vector<std::uint8_t> bytes{ 1, 2, 3 };
  iscool::net::byte_array non_empty(bytes.begin(), bytes.end());
  iscool::net::byte_array array;

  array.append(non_empty);
  EXPECT_EQ(bytes, std::vector<std::uint8_t>(array.begin(), array.end()));
}

TEST(byte_array_test, append_non_empty_to_non_empty)
{
  const std::vector<std::uint8_t> initial_bytes{ 1, 2, 3 };
  iscool::net::byte_array array(initial_bytes.begin(), initial_bytes.end());

  const std::vector<std::uint8_t> inserted_bytes{ 5, 6, 7 };
  const iscool::net::byte_array inserted(inserted_bytes.begin(),
                                         inserted_bytes.end());

  array.append(inserted);

  const std::vector<std::uint8_t> expected{ 1, 2, 3, 5, 6, 7 };
  EXPECT_EQ(expected, std::vector<std::uint8_t>(array.begin(), array.end()));
}

TEST(byte_array_test, append_range)
{
  const std::vector<std::uint8_t> initial_bytes{ 1, 2, 3 };
  iscool::net::byte_array array(initial_bytes.begin(), initial_bytes.end());

  const std::vector<std::uint8_t> inserted_bytes{ 5, 6, 7 };
  array.append(inserted_bytes.begin(), inserted_bytes.end());

  const std::vector<std::uint8_t> expected{ 1, 2, 3, 5, 6, 7 };
  EXPECT_EQ(expected, std::vector<std::uint8_t>(array.begin(), array.end()));
}

TEST(byte_array_test, swap)
{
  const std::vector<std::uint8_t> bytes_1{ 1, 2, 3 };
  iscool::net::byte_array array_1(bytes_1.begin(), bytes_1.end());

  const std::vector<std::uint8_t> bytes_2{ 5, 6 };
  iscool::net::byte_array array_2(bytes_2.begin(), bytes_2.end());

  array_1.swap(array_2);

  EXPECT_EQ(bytes_2,
            std::vector<std::uint8_t>(array_1.begin(), array_1.end()));
  EXPECT_EQ(bytes_1,
            std::vector<std::uint8_t>(array_2.begin(), array_2.end()));
}
