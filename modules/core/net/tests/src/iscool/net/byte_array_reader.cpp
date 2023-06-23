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

#include <gtest/gtest.h>

TEST(byte_array_reader_test, empty_has_next)
{
  EXPECT_FALSE(
      iscool::net::byte_array_reader(iscool::net::byte_array()).has_next());
}

TEST(byte_array_reader_test, non_empty_has_next)
{
  const std::vector<std::uint8_t> content{ 1 };
  const iscool::net::byte_array array(content.begin(), content.end());
  EXPECT_TRUE(iscool::net::byte_array_reader(array).has_next());
}

TEST(byte_array_reader_test, get8)
{
  const std::vector<std::uint8_t> content{ 1, 2, 3, 4 };
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);

  EXPECT_EQ(1, reader.get<std::uint8_t>());
  EXPECT_EQ(2, reader.get<std::uint8_t>());
  EXPECT_EQ(3, reader.get<std::uint8_t>());
  EXPECT_EQ(4, reader.get<std::uint8_t>());
}

TEST(byte_array_reader_test, get16)
{
  const std::vector<std::uint8_t> content{ 1, 2, 3, 4 };
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);

  EXPECT_EQ(0x0102, reader.get<std::uint16_t>());
  EXPECT_EQ(0x0304, reader.get<std::uint16_t>());
}

TEST(byte_array_reader_test, get32)
{
  const std::vector<std::uint8_t> content{ 1, 2, 3, 4, 5, 6, 7, 8 };
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);

  EXPECT_EQ(0x01020304u, reader.get<std::uint32_t>());
  EXPECT_EQ(0x05060708u, reader.get<std::uint32_t>());
}

TEST(byte_array_reader_test, get64)
{
  const std::vector<std::uint8_t> content{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf
  };
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);

  EXPECT_EQ(0x0001020304050607ull, reader.get<std::uint64_t>());
  EXPECT_EQ(0x08090a0b0c0d0e0full, reader.get<std::uint64_t>());
}

TEST(byte_array_reader_test, get_overflow_throws)
{
  const std::vector<std::uint8_t> content{ 1 };
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);

  EXPECT_THROW(reader.get<std::uint64_t>(), std::out_of_range);
}

TEST(byte_array_reader_test, slice_returns_remaining_bytes)
{
  const std::vector<std::uint8_t> content{ 1, 2, 3, 4 };
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);

  reader.get<std::uint8_t>();
  iscool::net::byte_array sliced(reader.slice());

  const std::vector<std::uint8_t> expected{ 2, 3, 4 };
  const std::vector<std::uint8_t> actual(sliced.begin(), sliced.end());

  EXPECT_EQ(expected, actual);
}

TEST(byte_array_reader_test, slice_does_not_change_source)
{
  const std::vector<std::uint8_t> content{ 1, 2, 3, 4 };
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);

  reader.get<std::uint8_t>();
  reader.slice();

  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(2, reader.get<std::uint8_t>());
}

TEST(byte_array_reader_test, slice_nreturns_next_nbytes)
{
  const std::vector<std::uint8_t> content{ 1, 2, 3, 4 };
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);

  reader.get<std::uint8_t>();
  iscool::net::byte_array sliced(reader.slice(2));

  const std::vector<std::uint8_t> expected{ 2, 3 };
  const std::vector<std::uint8_t> actual(sliced.begin(), sliced.end());

  EXPECT_EQ(expected, actual);
}

TEST(byte_array_reader_test, slice_ndoes_not_change_source)
{
  const std::vector<std::uint8_t> content{ 1, 2, 3, 4 };
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);

  reader.get<std::uint8_t>();
  reader.slice(2);

  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(2, reader.get<std::uint8_t>());
}

TEST(byte_array_reader_test, get_raw_moves_forward)
{
  const std::vector<std::uint8_t> content{ 1, 2, 3, 4 };
  const iscool::net::byte_array array(content.begin(), content.end());
  iscool::net::byte_array_reader reader(array);

  reader.get<std::uint8_t>();
  iscool::net::byte_array bytes(reader.get_raw(2));

  const std::vector<std::uint8_t> expected{ 2, 3 };
  const std::vector<std::uint8_t> actual(bytes.begin(), bytes.end());

  EXPECT_EQ(expected, actual);
  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(4, reader.get<std::uint8_t>());
}
