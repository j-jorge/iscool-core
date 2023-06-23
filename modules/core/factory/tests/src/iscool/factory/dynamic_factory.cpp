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
#include "iscool/factory/dynamic_factory.h"
#include "iscool/factory/dynamic_factory.impl.tpp"

#include "iscool/test/debug_crash.h"

#include <gtest/gtest.h>

TEST(iscool_factory_dynamic_factory, register_create_by_typename)
{
  iscool::factory::dynamic_factory<int> factory;

  factory.register_typename("ten",
                            []() -> int
                            {
                              return 10;
                            });

  EXPECT_EQ(10, factory.create_by_typename("ten"));

  factory.register_typename("twenty",
                            []() -> int
                            {
                              return 20;
                            });

  EXPECT_EQ(20, factory.create_by_typename("twenty"));
  EXPECT_EQ(10, factory.create_by_typename("ten"));
}

TEST(iscool_factory_dynamic_factory, register_create_by_typename_with_args)
{
  iscool::factory::dynamic_factory<int, int, int> factory;

  factory.register_typename("add",
                            [](int x, int y) -> int
                            {
                              return x + y;
                            });

  EXPECT_EQ(10, factory.create_by_typename("add", 6, 4));
  EXPECT_EQ(5, factory.create_by_typename("add", 3, 2));

  factory.register_typename("multiply",
                            [](int x, int y) -> int
                            {
                              return x * y;
                            });

  EXPECT_EQ(20, factory.create_by_typename("multiply", 2, 10));
  EXPECT_EQ(8, factory.create_by_typename("add", 5, 3));
}

TEST(iscool_factory_dynamic_factory, debug_fail_on_duplicate_name)
{
  iscool::factory::dynamic_factory<int> factory;

  const auto factory_function(
      []() -> int
      {
        return 0;
        ;
      });
  factory.register_typename("a", factory_function);
  EXPECT_DEBUG_CRASH(factory.register_typename("a", factory_function));
}

TEST(iscool_factory_dynamic_factory, debug_fail_on_create_unknown)
{
  iscool::factory::dynamic_factory<int> factory;

  EXPECT_DEBUG_CRASH(factory.create_by_typename("a"));
}
