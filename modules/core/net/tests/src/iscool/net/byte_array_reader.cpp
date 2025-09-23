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

TEST(byte_array_reader_test, empty)
{
  EXPECT_FALSE(iscool::net::byte_array_reader({}).has_next());
  EXPECT_EQ(0, iscool::net::byte_array_reader({}).remaining_bytes());
}

TEST(byte_array_reader_test, non_empty)
{
  const std::uint8_t bytes[] = { 1 };
  EXPECT_TRUE(iscool::net::byte_array_reader(bytes).has_next());
  EXPECT_EQ(1, iscool::net::byte_array_reader(bytes).remaining_bytes());
}

TEST(byte_array_reader_test, get8)
{
  const std::uint8_t bytes[] = { 1, 2, 3, 4 };
  iscool::net::byte_array_reader reader(bytes);

  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(4, reader.remaining_bytes());

  EXPECT_EQ(1, reader.get<std::uint8_t>());
  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(3, reader.remaining_bytes());

  EXPECT_EQ(2, reader.get<std::uint8_t>());
  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(2, reader.remaining_bytes());

  EXPECT_EQ(3, reader.get<std::uint8_t>());
  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(1, reader.remaining_bytes());

  EXPECT_EQ(4, reader.get<std::uint8_t>());
  EXPECT_FALSE(reader.has_next());
  EXPECT_EQ(0, reader.remaining_bytes());
}

TEST(byte_array_reader_test, get16)
{
  const std::uint8_t bytes[] = { 1, 2, 3, 4 };
  iscool::net::byte_array_reader reader(bytes);

  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(4, reader.remaining_bytes());

  EXPECT_EQ(0x0102, reader.get<std::uint16_t>());
  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(2, reader.remaining_bytes());

  EXPECT_EQ(0x0304, reader.get<std::uint16_t>());
  EXPECT_FALSE(reader.has_next());
  EXPECT_EQ(0, reader.remaining_bytes());
}

TEST(byte_array_reader_test, get32)
{
  const std::uint8_t bytes[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  iscool::net::byte_array_reader reader(bytes);

  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(8, reader.remaining_bytes());

  EXPECT_EQ(0x01020304u, reader.get<std::uint32_t>());
  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(4, reader.remaining_bytes());

  EXPECT_EQ(0x05060708u, reader.get<std::uint32_t>());
  EXPECT_FALSE(reader.has_next());
  EXPECT_EQ(0, reader.remaining_bytes());
}

TEST(byte_array_reader_test, get64)
{
  const std::uint8_t bytes[] = { 0, 1, 2,   3,   4,   5,   6,   7,
                                 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
  iscool::net::byte_array_reader reader(bytes);

  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(16, reader.remaining_bytes());

  EXPECT_EQ(0x0001020304050607ull, reader.get<std::uint64_t>());
  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(8, reader.remaining_bytes());

  EXPECT_EQ(0x08090a0b0c0d0e0full, reader.get<std::uint64_t>());
  EXPECT_FALSE(reader.has_next());
  EXPECT_EQ(0, reader.remaining_bytes());
}

TEST(byte_array_reader_test, get_overflow_throws)
{
  const std::uint8_t bytes[] = { 1 };
  iscool::net::byte_array_reader reader(bytes);

  EXPECT_THROW(reader.get<std::uint64_t>(), std::out_of_range);
}

TEST(byte_array_reader_test, raw_overflow_throws)
{
  const std::uint8_t bytes[] = { 1 };
  iscool::net::byte_array_reader reader(bytes);

  EXPECT_THROW(reader.raw(4), std::out_of_range);
}

TEST(byte_array_reader_test, raw_returns_remaining_bytes)
{
  const std::uint8_t bytes[] = { 1, 2, 3, 4 };
  iscool::net::byte_array_reader reader(bytes);

  reader.get<std::uint8_t>();
  const std::span<const std::uint8_t> raw(reader.raw());

  const std::vector<std::uint8_t> expected{ 2, 3, 4 };
  const std::vector<std::uint8_t> actual(raw.begin(), raw.end());

  EXPECT_EQ(expected, actual);

  EXPECT_FALSE(reader.has_next());
  EXPECT_EQ(0, reader.remaining_bytes());
}

TEST(byte_array_reader_test, raw_n_returns_next_n_bytes)
{
  const std::uint8_t bytes[] = { 1, 2, 3, 4 };
  iscool::net::byte_array_reader reader(bytes);

  reader.get<std::uint8_t>();
  const std::span<const std::uint8_t> raw(reader.raw(2));

  const std::vector<std::uint8_t> expected{ 2, 3 };
  const std::vector<std::uint8_t> actual(raw.begin(), raw.end());

  EXPECT_EQ(expected, actual);

  EXPECT_TRUE(reader.has_next());
  EXPECT_EQ(1, reader.remaining_bytes());
}
