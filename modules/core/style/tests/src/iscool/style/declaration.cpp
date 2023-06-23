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
#include <iscool/style/declaration.hpp>

#include <type_traits>

#include <gtest/gtest.h>

TEST(iscool_style_declaration, moveable)
{
  EXPECT_TRUE(std::is_move_constructible<iscool::style::declaration>::value);
  EXPECT_TRUE(std::is_move_assignable<iscool::style::declaration>::value);
}

TEST(iscool_style_declaration, merge_empty_declaration)
{
  iscool::style::declaration style;
  style.set_declaration("Sub", iscool::style::declaration());

  const iscool::style::declaration merged(
      iscool::style::declaration().merge(style));

  EXPECT_TRUE(!!merged.get_declaration("Sub"));
}
