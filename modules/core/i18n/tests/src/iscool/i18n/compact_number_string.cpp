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
#include "iscool/i18n/compact_number_string.h"

#include "gtest/gtest.h"

TEST(iscool_i18n, compact_number_string)
{
  EXPECT_EQ("10", iscool::i18n::compact_number_string(10));

  EXPECT_EQ("1.0k", iscool::i18n::compact_number_string(1000));
  EXPECT_EQ("1.4k", iscool::i18n::compact_number_string(1400));
  EXPECT_EQ("1.5k", iscool::i18n::compact_number_string(1480));
  EXPECT_EQ("1.0M", iscool::i18n::compact_number_string(999999));

  EXPECT_EQ("1.0M", iscool::i18n::compact_number_string(1000000));
  EXPECT_EQ("1.4M", iscool::i18n::compact_number_string(1400000));
  EXPECT_EQ("1.5M", iscool::i18n::compact_number_string(1480000));
}
