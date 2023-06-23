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
#include <iscool/collections/has_duplicates.hpp>

#include "gtest/gtest.h"

TEST(iscool_collections_has_duplicates, true)
{
  const std::vector<int> values = { 0, 1, 1, 8 };
  EXPECT_TRUE(
      iscool::collections::has_duplicates(values.begin(), values.end()));
}

TEST(iscool_collections_has_duplicates, false)
{
  const std::vector<int> values = { 0, 1, 5, 8 };
  EXPECT_FALSE(
      iscool::collections::has_duplicates(values.begin(), values.end()));
}

TEST(iscool_collections_has_duplicates, pointer)
{
  const int values[4] = { 0, 5, 5, 8 };
  EXPECT_TRUE(iscool::collections::has_duplicates(values, values + 4));
}
