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
#include "iscool/meta/underlying_type.h"

#include "gtest/gtest.h"

TEST(iscool_meta_underlying_type, int)
{
  const bool same(
      std::is_same<int, iscool::meta::underlying_type<int>::type>::value);

  EXPECT_TRUE(same);
}

TEST(iscool_meta_underlying_type, string)
{
  const bool same(
      std::is_same<std::string,
                   iscool::meta::underlying_type<std::string>::type>::value);

  EXPECT_TRUE(same);
}

TEST(iscool_meta_underlying_type, enum)
{
  enum class enum_type : std::int64_t;

  const bool same(
      std::is_same<std::int64_t,
                   iscool::meta::underlying_type<enum_type>::type>::value);

  EXPECT_TRUE(same);
}

TEST(iscool_meta_underlying_type, enum_char)
{
  enum class enum_type : char;

  const bool same(
      std::is_same<char,
                   iscool::meta::underlying_type<enum_type>::type>::value);

  EXPECT_TRUE(same);
}
