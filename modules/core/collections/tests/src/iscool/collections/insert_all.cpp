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
#include <iscool/collections/insert_all.hpp>

#include <iscool/test/equal_collections.hpp>

#include "gtest/gtest.h"

#include <map>

TEST(iscool_collections_insert_all, set)
{
  std::set<int> output = { { 1, 3, 5 } };
  const std::set<int> input = { { 2, 3, 4 } };

  const std::vector<int> expected_result({ 1, 2, 3, 4, 5 });

  iscool::collections::insert_all(output, input);

  iscool::test::assert_equal_collections(output, expected_result);
}

TEST(iscool_collections_insert_all, map)
{
  std::map<int, double> output = { { 1, 1.0 }, { 3, 3.0 }, { 5, 5.0 } };
  const std::map<int, double> input = { { 2, 2.0 }, { 3, 3.5 }, { 4, 4.0 } };

  const std::map<int, double> expected_result = {
    { 1, 1.0 }, { 2, 2.0 }, { 3, 3.0 }, { 4, 4.0 }, { 5, 5.0 }
  };

  iscool::collections::insert_all(output, input);

  iscool::test::assert_equal_collections(output, expected_result);
}
