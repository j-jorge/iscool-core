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
#include <iscool/meta/contains.hpp>

#include "gtest/gtest.h"

TEST(iscool_meta_contains, true)
{
  const bool result(
      iscool::meta::contains<int, std::string, int, float>::value);

  EXPECT_TRUE(result);
}

TEST(iscool_meta_contains, false)
{
  const bool result(
      iscool::meta::contains<double, std::string, int, float>::value);

  EXPECT_FALSE(result);
}

TEST(iscool_meta_contains, typedef)
{
  typedef int type;

  const bool result(
      iscool::meta::contains<type, std::string, int, float>::value);

  EXPECT_TRUE(result);
}
