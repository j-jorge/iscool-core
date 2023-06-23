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
#include <iscool/net/byte_array_from_stream.hpp>

#include <sstream>

#include <gtest/gtest.h>

TEST(byte_array_from_stream, result)
{
  const char bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0 };

  std::istringstream stream(bytes);

  const iscool::net::byte_array array(
      iscool::net::byte_array_from_stream(stream));

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
