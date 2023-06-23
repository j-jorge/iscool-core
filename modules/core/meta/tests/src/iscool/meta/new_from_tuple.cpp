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
#include "iscool/meta/new_from_tuple.h"

#include <functional>

#include <gtest/gtest.h>

namespace iscool
{
  namespace meta
  {
    namespace tests
    {
      class copy_counter
      {
      public:
        copy_counter();
        copy_counter(const copy_counter& that);
        copy_counter(copy_counter&& that);

        copy_counter& operator=(const copy_counter& that);
        copy_counter& operator=(copy_counter&& that);

      public:
        int copy = 0;
        int move = 0;
        int copy_assign = 0;
        int move_assign = 0;
      };

      class new_from_tuple_type
      {
      public:
        new_from_tuple_type(int int_value, float float_value,
                            const copy_counter& c);

      public:
        int int_value;
        float float_value;
        const copy_counter& counter;
      };
    }
  }
}

iscool::meta::tests::copy_counter::copy_counter() = default;

iscool::meta::tests::copy_counter::copy_counter(const copy_counter& that)
{
  ++copy;
}

iscool::meta::tests::copy_counter::copy_counter(copy_counter&& that)
{
  ++move;
}

iscool::meta::tests::copy_counter&
iscool::meta::tests::copy_counter::operator=(const copy_counter& that)
{
  ++copy_assign;
  return *this;
}

iscool::meta::tests::copy_counter&
iscool::meta::tests::copy_counter::operator=(copy_counter&& that)
{
  ++move_assign;
  return *this;
}

iscool::meta::tests::new_from_tuple_type::new_from_tuple_type(
    int int_value, float float_value, const copy_counter& counter)
  : int_value(int_value)
  , float_value(float_value)
  , counter(counter)
{}

TEST(iscool_meta_new_from_tuple, forward_arguments)
{
  iscool::meta::tests::copy_counter copy_counter;

  std::unique_ptr<iscool::meta::tests::new_from_tuple_type> p(
      iscool::meta::new_from_tuple<iscool::meta::tests::new_from_tuple_type>(
          std::make_tuple(1, 2.6f, std::cref(copy_counter))));

  EXPECT_NE(nullptr, p);

  EXPECT_EQ(1, p->int_value);
  EXPECT_FLOAT_EQ(2.6, p->float_value);
  EXPECT_EQ(&copy_counter, &p->counter);

  EXPECT_EQ(0, copy_counter.copy);
  EXPECT_EQ(0, copy_counter.move);
  EXPECT_EQ(0, copy_counter.copy_assign);
  EXPECT_EQ(0, copy_counter.move_assign);
}

TEST(iscool_meta_new_from_tuple, no_arguments)
{
  std::unique_ptr<std::string> p(
      iscool::meta::new_from_tuple<std::string>(std::make_tuple()));

  EXPECT_NE(nullptr, p);
  EXPECT_TRUE(p->empty());
}
