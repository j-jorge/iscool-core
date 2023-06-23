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
#include "iscool/i18n/numeric.h"

#include "gtest/gtest.h"

TEST(iscool_i18n_numeric, long_long_to_string)
{
  EXPECT_EQ("10", iscool::i18n::numeric::to_string(10ll));
  EXPECT_EQ("1,000", iscool::i18n::numeric::to_string(1000ll));
  EXPECT_EQ("-2,405", iscool::i18n::numeric::to_string(-2405ll));
  EXPECT_EQ("1,200,300", iscool::i18n::numeric::to_string(1200300ll));
  EXPECT_EQ("20,400,200,300", iscool::i18n::numeric::to_string(20400200300ll));
  EXPECT_EQ("-20,400,200,300",
            iscool::i18n::numeric::to_string(-20400200300ll));
}

TEST(iscool_i18n_numeric, long_to_string)
{
  EXPECT_EQ("10", iscool::i18n::numeric::to_string(10l));
  EXPECT_EQ("1,000", iscool::i18n::numeric::to_string(1000l));
  EXPECT_EQ("-2,405", iscool::i18n::numeric::to_string(-2405l));
  EXPECT_EQ("1,200,300", iscool::i18n::numeric::to_string(1200300l));
}

TEST(iscool_i18n_numeric, int_to_string)
{
  EXPECT_EQ("10", iscool::i18n::numeric::to_string(10));
  EXPECT_EQ("1,000", iscool::i18n::numeric::to_string(1000));
  EXPECT_EQ("-2,405", iscool::i18n::numeric::to_string(-2405));
  EXPECT_EQ("1,200,300", iscool::i18n::numeric::to_string(1200300));
}

TEST(iscool_i18n_numeric, short_to_string)
{
  EXPECT_EQ("10", iscool::i18n::numeric::to_string(short(10)));
  EXPECT_EQ("1,000", iscool::i18n::numeric::to_string(short(1000)));
  EXPECT_EQ("-2,405", iscool::i18n::numeric::to_string(short(-2405)));
  EXPECT_EQ("12,300", iscool::i18n::numeric::to_string(short(12300)));
}

TEST(iscool_i18n_numeric, char_to_string)
{
  EXPECT_EQ("10", iscool::i18n::numeric::to_string(char(10)));
  EXPECT_EQ("-100", iscool::i18n::numeric::to_string(char(-100)));
}

TEST(iscool_i18n_numeric, unsigned_long_long_to_string)
{
  EXPECT_EQ("10", iscool::i18n::numeric::to_string(10ull));
  EXPECT_EQ("1,000", iscool::i18n::numeric::to_string(1000ull));
  EXPECT_EQ("1,200,300", iscool::i18n::numeric::to_string(1200300ull));
  EXPECT_EQ("20,400,200,300",
            iscool::i18n::numeric::to_string(20400200300ull));
}

TEST(iscool_i18n_numeric, unsigned_long_to_string)
{
  EXPECT_EQ("10", iscool::i18n::numeric::to_string(10ul));
  EXPECT_EQ("1,000", iscool::i18n::numeric::to_string(1000ul));
  EXPECT_EQ("1,200,300", iscool::i18n::numeric::to_string(1200300ul));
}

TEST(iscool_i18n_numeric, unsigned_int_to_string)
{
  EXPECT_EQ("10", iscool::i18n::numeric::to_string(10u));
  EXPECT_EQ("1,000", iscool::i18n::numeric::to_string(1000u));
  EXPECT_EQ("1,200,300", iscool::i18n::numeric::to_string(1200300u));
}

TEST(iscool_i18n_numeric, unsigned_short_to_string)
{
  EXPECT_EQ("10", iscool::i18n::numeric::to_string((unsigned short)10));
  EXPECT_EQ("1,000", iscool::i18n::numeric::to_string((unsigned short)1000));
  EXPECT_EQ("12,300", iscool::i18n::numeric::to_string((unsigned short)12300));
}

TEST(iscool_i18n_numeric, unsigned_char_to_string)
{
  EXPECT_EQ("10", iscool::i18n::numeric::to_string((unsigned char)10));
}
