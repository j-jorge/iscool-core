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
#include <iscool/collections/binary_search.hpp>

#include <gtest/gtest.h>

namespace iscool
{
  namespace collections
  {
    namespace tests
    {
      class int_compare
      {
      public:
        explicit int_compare(int rhs);

        int operator()(int lhs) const;

      private:
        const int _rhs;
      };
    }
  }
}

iscool::collections::tests::int_compare::int_compare(int rhs)
  : _rhs(rhs)
{}

int iscool::collections::tests::int_compare::operator()(int lhs) const
{
  return lhs - _rhs;
}

TEST(iscool_collections_binary_search, empty)
{
  const std::vector<int> values;

  EXPECT_EQ(values.end(), iscool::collections::binary_search(
                              values.begin(), values.end(),
                              iscool::collections::tests::int_compare(10)));
}

TEST(iscool_collections_binary_search, singleton)
{
  const std::vector<int> values({ 10 });

  const auto begin(values.begin());
  const auto end(values.end());

  EXPECT_EQ(end, iscool::collections::binary_search(
                     begin, end, iscool::collections::tests::int_compare(20)));
  EXPECT_EQ(begin,
            iscool::collections::binary_search(
                begin, end, iscool::collections::tests::int_compare(10)));
}

TEST(iscool_collections_binary_search, two_values)
{
  const std::vector<int> values({ 10, 20 });

  const auto begin(values.begin());
  const auto end(values.end());

  EXPECT_EQ(begin,
            iscool::collections::binary_search(
                begin, end, iscool::collections::tests::int_compare(10)));
  EXPECT_EQ(begin + 1,
            iscool::collections::binary_search(
                begin, end, iscool::collections::tests::int_compare(20)));
  EXPECT_EQ(end, iscool::collections::binary_search(
                     begin, end, iscool::collections::tests::int_compare(30)));
}

TEST(iscool_collections_binary_search, 5_values)
{
  const std::vector<int> values({ 10, 20, 30, 30, 40 });

  const auto begin(values.begin());
  const auto end(values.end());

  EXPECT_EQ(begin,
            iscool::collections::binary_search(
                begin, end, iscool::collections::tests::int_compare(10)));
  EXPECT_EQ(begin + 1,
            iscool::collections::binary_search(
                begin, end, iscool::collections::tests::int_compare(20)));

  const auto duplicate_it(iscool::collections::binary_search(
      begin, end, iscool::collections::tests::int_compare(30)));

  EXPECT_TRUE((duplicate_it == begin + 2) || (duplicate_it == begin + 3));

  EXPECT_EQ(begin + 4,
            iscool::collections::binary_search(
                begin, end, iscool::collections::tests::int_compare(40)));
  EXPECT_EQ(end, iscool::collections::binary_search(
                     begin, end, iscool::collections::tests::int_compare(50)));
}
