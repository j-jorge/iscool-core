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
#include <iscool/enum_equals.hpp>

#include <gtest/gtest.h>

namespace iscool
{
  namespace test
  {
    enum class enum_1
    {
      a,
      b
    };

    enum class enum_2
    {
      a = 3,
      b = 6,
      c = 3
    };
  }
}

TEST(iscool_enum_equals, int_and_enum)
{
  EXPECT_TRUE(iscool::enum_equals(0, iscool::test::enum_1::a));
  EXPECT_FALSE(iscool::enum_equals(1, iscool::test::enum_1::a));
  EXPECT_TRUE(iscool::enum_equals(1, iscool::test::enum_1::b));
  EXPECT_FALSE(iscool::enum_equals(2, iscool::test::enum_1::b));

  EXPECT_FALSE(iscool::enum_equals(1, iscool::test::enum_2::a));
  EXPECT_TRUE(iscool::enum_equals(3, iscool::test::enum_2::a));
  EXPECT_TRUE(iscool::enum_equals(6, iscool::test::enum_2::b));
  EXPECT_TRUE(iscool::enum_equals(3, iscool::test::enum_2::c));
  EXPECT_FALSE(iscool::enum_equals(3, iscool::test::enum_2::b));
  EXPECT_FALSE(iscool::enum_equals(6, iscool::test::enum_2::a));
}

TEST(iscool_enum_equals, enum_and_int)
{
  EXPECT_TRUE(iscool::enum_equals(iscool::test::enum_1::a, 0));
  EXPECT_FALSE(iscool::enum_equals(iscool::test::enum_1::a, 1));
  EXPECT_TRUE(iscool::enum_equals(iscool::test::enum_1::b, 1));
  EXPECT_FALSE(iscool::enum_equals(iscool::test::enum_1::b, 2));

  EXPECT_FALSE(iscool::enum_equals(iscool::test::enum_2::a, 1));
  EXPECT_TRUE(iscool::enum_equals(iscool::test::enum_2::a, 3));
  EXPECT_TRUE(iscool::enum_equals(iscool::test::enum_2::b, 6));
  EXPECT_TRUE(iscool::enum_equals(iscool::test::enum_2::c, 3));
  EXPECT_FALSE(iscool::enum_equals(iscool::test::enum_2::b, 3));
  EXPECT_FALSE(iscool::enum_equals(iscool::test::enum_2::a, 6));
}
