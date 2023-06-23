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
#include "iscool/copy.h"

#include <string>

#include <gtest/gtest.h>

TEST(iscool_copy, int)
{
  int value(24);
  const int& copy(iscool::copy(value));

  EXPECT_EQ(24, copy);
  EXPECT_NE(&value, &copy);
}

TEST(iscool_copy, string)
{
  std::string value("test");
  const std::string& copy(iscool::copy(value));

  EXPECT_EQ("test", copy);
  EXPECT_EQ("test", value);
  EXPECT_NE(&value, &copy);
}
