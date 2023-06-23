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
#include "iscool/collections/rank.h"

#include <gtest/gtest.h>

TEST(iscool_collections_ranks, empty)
{
  const std::vector<int> values({});

  iscool::collections::rank(values.begin(), values.end(),
                            [](std::size_t rank) -> void
                            {
                              EXPECT_FALSE(true);
                            });
}

TEST(iscool_collections_ranks, increasing_order_no_duplicates)
{
  const std::vector<int> values({ 5, 8, 9 });
  std::vector<int> ranks;

  iscool::collections::rank(values.begin(), values.end(),
                            [&](std::size_t rank) -> void
                            {
                              ranks.push_back(rank);
                            });

  EXPECT_EQ(values.size(), ranks.size());
  EXPECT_EQ(1, ranks[0]);
  EXPECT_EQ(2, ranks[1]);
  EXPECT_EQ(3, ranks[2]);
}

TEST(iscool_collections_ranks, increasing_order_duplicates)
{
  const std::vector<int> values({ 5, 8, 8, 9, 12, 12, 15 });
  std::vector<int> ranks;

  iscool::collections::rank(values.begin(), values.end(),
                            [&](std::size_t rank) -> void
                            {
                              ranks.push_back(rank);
                            });

  EXPECT_EQ(values.size(), ranks.size());
  EXPECT_EQ(1, ranks[0]);
  EXPECT_EQ(2, ranks[1]);
  EXPECT_EQ(2, ranks[2]);
  EXPECT_EQ(4, ranks[3]);
  EXPECT_EQ(5, ranks[4]);
  EXPECT_EQ(5, ranks[5]);
  EXPECT_EQ(7, ranks[6]);
}

TEST(iscool_collections_ranks, decreasing_order_no_duplicates)
{
  const std::vector<int> values({ 95, 8, 5 });
  std::vector<int> ranks;

  iscool::collections::rank(values.begin(), values.end(),
                            [&](std::size_t rank) -> void
                            {
                              ranks.push_back(rank);
                            });

  EXPECT_EQ(values.size(), ranks.size());
  EXPECT_EQ(1, ranks[0]);
  EXPECT_EQ(2, ranks[1]);
  EXPECT_EQ(3, ranks[2]);
}

TEST(iscool_collections_ranks, decreasing_order_duplicates)
{
  const std::vector<int> values({ 15, 12, 12, 9, 8, 8, 5 });
  std::vector<int> ranks;

  iscool::collections::rank(values.begin(), values.end(),
                            [&](std::size_t rank) -> void
                            {
                              ranks.push_back(rank);
                            });

  EXPECT_EQ(values.size(), ranks.size());
  EXPECT_EQ(1, ranks[0]);
  EXPECT_EQ(2, ranks[1]);
  EXPECT_EQ(2, ranks[2]);
  EXPECT_EQ(4, ranks[3]);
  EXPECT_EQ(5, ranks[4]);
  EXPECT_EQ(5, ranks[5]);
  EXPECT_EQ(7, ranks[6]);
}

TEST(iscool_collections_ranks, custom_order_empty)
{
  const std::vector<int> values({ 12, 15, 8, 12, 9, 5, 8 });
  const std::vector<std::size_t> order;

  iscool::collections::rank(values.begin(), order.begin(), order.end(),
                            [](std::size_t rank) -> void
                            {
                              EXPECT_FALSE(true);
                            });
}

TEST(iscool_collections_ranks, custom_order_duplicates)
{
  const std::vector<int> values({ 12, 15, 8, 12, 9, 5, 8 });
  const std::vector<std::size_t> order({ 5, 2, 6, 4, 3, 0, 1 });
  std::vector<int> ranks;

  iscool::collections::rank(values.begin(), order.begin(), order.end(),
                            [&](std::size_t rank) -> void
                            {
                              ranks.push_back(rank);
                            });

  EXPECT_EQ(values.size(), ranks.size());
  EXPECT_EQ(1, ranks[0]);
  EXPECT_EQ(2, ranks[1]);
  EXPECT_EQ(2, ranks[2]);
  EXPECT_EQ(4, ranks[3]);
  EXPECT_EQ(5, ranks[4]);
  EXPECT_EQ(5, ranks[5]);
  EXPECT_EQ(7, ranks[6]);
}
