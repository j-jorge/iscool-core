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
#include "iscool/locale/character_range.h"

#include <gtest/gtest.h>

TEST(iscool_locale, make_character_range_empty)
{
  const iscool::locale::character_range range(
      iscool::locale::make_character_range(""));

  ASSERT_EQ(range.end(), range.begin());
}

TEST(iscool_locale, make_character_range)
{
  const std::string characters = "aïÏs Ößל$";
  const iscool::locale::character_range range(
      iscool::locale::make_character_range(characters));

  ASSERT_EQ(9, std::distance(range.begin(), range.end()));

  auto it(range.begin());

  EXPECT_EQ("a", *it);
  ++it;

  EXPECT_EQ("ï", *it);
  ++it;

  EXPECT_EQ("Ï", *it);
  ++it;

  EXPECT_EQ("s", *it);
  ++it;

  EXPECT_EQ(" ", *it);
  ++it;

  EXPECT_EQ("Ö", *it);
  ++it;

  EXPECT_EQ("ß", *it);
  ++it;

  EXPECT_EQ("ל", *it);
  ++it;

  EXPECT_EQ("$", *it);
  ++it;

  EXPECT_EQ(range.end(), it);
}
