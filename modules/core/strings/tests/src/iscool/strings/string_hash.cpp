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
#include <iscool/strings/dynamic_hash.hpp>
#include <iscool/strings/string_hash.hpp>

#include <gtest/gtest.h>

TEST(iscool_strings_string_hash, dynamic_hash_equals_static_hash)
{
  EXPECT_EQ(iscool::strings::dynamic_hash("abc"),
            iscool::strings::str_const("abc").hash());
}

TEST(iscool_strings_string_hash, string_hash_equals_static_hash)
{
  EXPECT_EQ(iscool::strings::str_const("abc").hash(),
            iscool::strings::string_hash("abc").get_hash_code());
}

TEST(iscool_strings_string_hash, string_hash_std_string)
{
  const std::string s("abc");

  EXPECT_EQ(iscool::strings::dynamic_hash(s.c_str()),
            iscool::strings::string_hash(s).get_hash_code());
}
