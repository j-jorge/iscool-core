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
#include "iscool/iterators/cycle_iterator.h"
#include "iscool/iterators/cycle_iterator.impl.tpp"

#include "iscool/test/debug_crash.h"

#include <vector>

#include <gtest/gtest.h>

TEST(iscool_iterators_cycle_iterator, fail_if_empty)
{
  static const char* p = "";
  (void)p;

  EXPECT_DEBUG_CRASH(iscool::iterators::cycle_iterator<const char*>(p, p));
}

TEST(iscool_iterators_cycle_iterator, pre_increment)
{
  static const std::vector<int> range({ 0, 1, 2 });

  typedef std::vector<int>::const_iterator iterator;

  iscool::iterators::cycle_iterator<iterator> it(range.begin(), range.end());

  iscool::iterators::cycle_iterator<iterator> pre(++it);

  EXPECT_EQ(1, *pre);
  EXPECT_EQ(1, *it);
}

TEST(iscool_iterators_cycle_iterator, post_increment)
{
  static const std::vector<int> range({ 0, 1, 2 });

  typedef std::vector<int>::const_iterator iterator;

  iscool::iterators::cycle_iterator<iterator> it(range.begin(), range.end());

  iscool::iterators::cycle_iterator<iterator> post(it++);

  EXPECT_EQ(0, *post);
  EXPECT_EQ(1, *it);
}

TEST(iscool_iterators_cycle_iterator, single)
{
  static const char* p = "abc";

  iscool::iterators::cycle_iterator<const char*> it(p, p + 1);

  EXPECT_EQ('a', *it);
  ++it;

  EXPECT_EQ('a', *it);
  ++it;

  EXPECT_EQ('a', *it);
}

TEST(iscool_iterators_cycle_iterator, loop)
{
  static std::vector<int> range(3, 0);

  typedef std::vector<int>::iterator iterator;

  iscool::iterators::cycle_iterator<iterator> it(range.begin(), range.end());

  *it = 1;
  ++it;

  *it = 2;
  ++it;

  *it = 3;
  ++it;

  EXPECT_EQ(1, range[0]);
  EXPECT_EQ(2, range[1]);
  EXPECT_EQ(3, range[2]);

  *it = 2;
  ++it;

  *it = 4;
  ++it;

  *it = 6;
  ++it;

  EXPECT_EQ(2, range[0]);
  EXPECT_EQ(4, range[1]);
  EXPECT_EQ(6, range[2]);
}

TEST(iscool_iterators_cycle_iterator, member_of_pointer)
{
  static std::vector<std::pair<int, int>> range({ { 3, 6 } });

  typedef std::vector<std::pair<int, int>>::iterator iterator;

  iscool::iterators::cycle_iterator<iterator> it(range.begin(), range.end());

  EXPECT_EQ(3, it->first);
  it->second = 43;

  EXPECT_EQ(43, it->second);
}
