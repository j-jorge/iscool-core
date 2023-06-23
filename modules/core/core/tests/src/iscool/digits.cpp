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
#include "iscool/digits.h"

#include <cmath>
#include <limits>

#include <gtest/gtest.h>

TEST(iscool_digits, non_negative)
{
  EXPECT_EQ(1, iscool::digits(0));
  EXPECT_EQ(1, iscool::digits(2));
  EXPECT_EQ(1, iscool::digits(9));

  EXPECT_EQ(2, iscool::digits(10));
  EXPECT_EQ(2, iscool::digits(55));

  EXPECT_EQ(3, iscool::digits(100));
  EXPECT_EQ(3, iscool::digits(555));

  EXPECT_EQ(4, iscool::digits(1000));
  EXPECT_EQ(4, iscool::digits(5555));

  EXPECT_EQ(5, iscool::digits(10000));
  EXPECT_EQ(5, iscool::digits(55555));

  EXPECT_EQ(6, iscool::digits(100000));
  EXPECT_EQ(6, iscool::digits(555555));

  EXPECT_EQ(7, iscool::digits(1000000));
  EXPECT_EQ(7, iscool::digits(5555555));

  EXPECT_EQ(8, iscool::digits(10000000));
  EXPECT_EQ(8, iscool::digits(55555555));

  EXPECT_EQ(9, iscool::digits(100000000));
  EXPECT_EQ(9, iscool::digits(555555555));

  EXPECT_EQ(10, iscool::digits(1000000000));
  EXPECT_EQ(10, iscool::digits(5555555555));

  EXPECT_EQ(11, iscool::digits(10000000000));
  EXPECT_EQ(11, iscool::digits(55555555555));

  EXPECT_EQ(12, iscool::digits(100000000000));
  EXPECT_EQ(12, iscool::digits(555555555555));

  EXPECT_EQ(13, iscool::digits(1000000000000));
  EXPECT_EQ(13, iscool::digits(5555555555555));

  EXPECT_EQ(14, iscool::digits(10000000000000));
  EXPECT_EQ(14, iscool::digits(55555555555555));

  EXPECT_EQ(15, iscool::digits(100000000000000));
  EXPECT_EQ(15, iscool::digits(555555555555555));

  EXPECT_EQ(16, iscool::digits(1000000000000000));
  EXPECT_EQ(16, iscool::digits(5555555555555555));

  EXPECT_EQ(17, iscool::digits(10000000000000000));
  EXPECT_EQ(17, iscool::digits(55555555555555555));

  EXPECT_EQ(18, iscool::digits(100000000000000000));
  EXPECT_EQ(18, iscool::digits(555555555555555555));

  EXPECT_EQ(19, iscool::digits(1000000000000000000));
  EXPECT_EQ(19, iscool::digits(5555555555555555555));

  EXPECT_EQ(19, iscool::digits(std::numeric_limits<std::int64_t>::max()));
}

TEST(iscool_digits, negative)
{
  EXPECT_EQ(2, iscool::digits(-1));
  EXPECT_EQ(2, iscool::digits(-5));

  EXPECT_EQ(3, iscool::digits(-10));
  EXPECT_EQ(3, iscool::digits(-55));

  EXPECT_EQ(4, iscool::digits(-100));
  EXPECT_EQ(4, iscool::digits(-555));

  EXPECT_EQ(5, iscool::digits(-1000));
  EXPECT_EQ(5, iscool::digits(-5555));

  EXPECT_EQ(6, iscool::digits(-10000));
  EXPECT_EQ(6, iscool::digits(-55555));

  EXPECT_EQ(7, iscool::digits(-100000));
  EXPECT_EQ(7, iscool::digits(-555555));

  EXPECT_EQ(8, iscool::digits(-1000000));
  EXPECT_EQ(8, iscool::digits(-5555555));

  EXPECT_EQ(9, iscool::digits(-10000000));
  EXPECT_EQ(9, iscool::digits(-55555555));

  EXPECT_EQ(10, iscool::digits(-100000000));
  EXPECT_EQ(10, iscool::digits(-555555555));

  EXPECT_EQ(11, iscool::digits(-1000000000));
  EXPECT_EQ(11, iscool::digits(-5555555555));

  EXPECT_EQ(12, iscool::digits(-10000000000));
  EXPECT_EQ(12, iscool::digits(-55555555555));

  EXPECT_EQ(13, iscool::digits(-100000000000));
  EXPECT_EQ(13, iscool::digits(-555555555555));

  EXPECT_EQ(14, iscool::digits(-1000000000000));
  EXPECT_EQ(14, iscool::digits(-5555555555555));

  EXPECT_EQ(15, iscool::digits(-10000000000000));
  EXPECT_EQ(15, iscool::digits(-55555555555555));

  EXPECT_EQ(16, iscool::digits(-100000000000000));
  EXPECT_EQ(16, iscool::digits(-555555555555555));

  EXPECT_EQ(17, iscool::digits(-1000000000000000));
  EXPECT_EQ(17, iscool::digits(-5555555555555555));

  EXPECT_EQ(18, iscool::digits(-10000000000000000));
  EXPECT_EQ(18, iscool::digits(-55555555555555555));

  EXPECT_EQ(19, iscool::digits(-100000000000000000));
  EXPECT_EQ(19, iscool::digits(-555555555555555555));

  EXPECT_EQ(20, iscool::digits(std::numeric_limits<std::int64_t>::min()));
}
