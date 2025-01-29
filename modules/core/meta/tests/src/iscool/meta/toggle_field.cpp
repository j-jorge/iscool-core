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
#include <iscool/meta/declare_toggle_field.hpp>
#include <iscool/meta/implement_toggle_field.hpp>

#include <gtest/gtest.h>

namespace iscool
{
  namespace meta
  {
    namespace test
    {
      class toggle_field_test
      {
      ic_declare_toggle_field(enabled)

          public : toggle_field_test();
        explicit toggle_field_test(bool initial_value);

        void changed();

      public:
        int call_count = 0;
      };
    }
  }
}

ic_implement_toggle_field(iscool::meta::test::toggle_field_test, enabled,
                          changed());

iscool::meta::test::toggle_field_test::toggle_field_test() = default;

iscool::meta::test::toggle_field_test::toggle_field_test(bool initial_value)
  : _enabled_toggle_state(initial_value)
{}

void iscool::meta::test::toggle_field_test::changed()
{
  ++call_count;
}

TEST(iscool_meta_toggle_field_test, notifies_changes)
{
  iscool::meta::test::toggle_field_test test;

  EXPECT_EQ(0, test.call_count);
  EXPECT_FALSE(test.is_enabled());

  test.set_enabled(false);

  EXPECT_EQ(0, test.call_count);
  EXPECT_FALSE(test.is_enabled());

  test.set_enabled(true);

  EXPECT_EQ(1, test.call_count);
  EXPECT_TRUE(test.is_enabled());

  test.set_enabled(true);

  EXPECT_EQ(1, test.call_count);
  EXPECT_TRUE(test.is_enabled());

  test.set_enabled(false);

  EXPECT_EQ(2, test.call_count);
  EXPECT_FALSE(test.is_enabled());
}

TEST(iscool_meta_toggle_field_test, explicit_initial_value)
{
  iscool::meta::test::toggle_field_test test(true);

  EXPECT_EQ(0, test.call_count);
  EXPECT_TRUE(test.is_enabled());

  test.set_enabled(false);

  EXPECT_EQ(1, test.call_count);
  EXPECT_FALSE(test.is_enabled());

  test.set_enabled(true);

  EXPECT_EQ(2, test.call_count);
  EXPECT_TRUE(test.is_enabled());
}
