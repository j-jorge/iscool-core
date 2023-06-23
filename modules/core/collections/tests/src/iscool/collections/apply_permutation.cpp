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
#include <iscool/collections/apply_permutation.hpp>

#include <gtest/gtest.h>

TEST(iscool_collections_apply_permutations, empty)
{
  std::vector<int> values({});
  const std::vector<std::size_t> permutation({});

  iscool::collections::apply_permutation(values.begin(), values.end(),
                                         permutation);

  EXPECT_TRUE(values.empty());
}

TEST(iscool_collections_apply_permutations, permutation)
{
  std::vector<int> values({ 9, 5, 8 });
  const std::vector<std::size_t> permutation({ 1, 2, 0 });

  iscool::collections::apply_permutation(values.begin(), values.end(),
                                         permutation);

  EXPECT_EQ(5, values[0]);
  EXPECT_EQ(8, values[1]);
  EXPECT_EQ(9, values[2]);
}

TEST(iscool_collections_apply_permutations, partial)
{
  std::vector<int> values({ 10, 9, 5, 8, 1 });
  const std::vector<std::size_t> permutation({ 1, 0, 2 });

  iscool::collections::apply_permutation(values.begin() + 1, values.end() - 1,
                                         permutation);

  EXPECT_EQ(10, values[0]);
  EXPECT_EQ(5, values[1]);
  EXPECT_EQ(9, values[2]);
  EXPECT_EQ(8, values[3]);
  EXPECT_EQ(1, values[4]);
}
