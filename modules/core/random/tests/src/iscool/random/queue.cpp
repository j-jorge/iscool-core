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
#include "iscool/random/random_queue.h"

#include <gtest/gtest.h>

TEST(iscool_random_queue, next_fail_if_empty)
{
  iscool::random::random_queue<int> queue;
  ASSERT_THROW(queue.next(), std::out_of_range);
}

TEST(iscool_random_queue, returns_one_of_each)
{
  iscool::random::random_queue<int> queue;
  const std::size_t count(10);

  for (std::size_t i(0); i != count; ++i)
    queue.insert(i);

  std::set<int> result;

  for (std::size_t i(0); i != count; ++i)
    result.insert(queue.next());

  EXPECT_EQ(count, result.size());
}

TEST(iscool_random_queue, regenerate)
{
  iscool::random::random_queue<int> queue;
  const std::size_t count(10);

  for (std::size_t i(0); i != count; ++i)
    queue.insert(i);

  std::set<int> first_sequence;

  for (std::size_t i(0); i != count; ++i)
    first_sequence.insert(queue.next());

  std::set<int> second_sequence;

  for (std::size_t i(0); i != count; ++i)
    second_sequence.insert(queue.next());

  EXPECT_EQ(count, second_sequence.size());
}

TEST(iscool_random_queue, dynamic_isert)
{
  iscool::random::random_queue<int> queue;
  const std::size_t count(10);

  for (std::size_t i(0); i != count; ++i)
    queue.insert(i);

  std::set<int> result;

  for (std::size_t i(0); i != count + 1; ++i)
    {
      if (i == count / 2)
        queue.insert(count);

      result.insert(queue.next());
    }

  EXPECT_EQ(count + 1, result.size());
}
