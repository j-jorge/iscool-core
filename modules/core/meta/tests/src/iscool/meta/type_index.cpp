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
#include <iscool/meta/type_index.hpp>

#include "gtest/gtest.h"

TEST(iscool_meta_type_index, index)
{
  const std::size_t first(
      iscool::meta::type_index<int, int, std::string, float>::value);

  EXPECT_EQ(std::size_t(0), first);

  const std::size_t anywhere(
      iscool::meta::type_index<int, float, double, int, char>::value);

  EXPECT_EQ(std::size_t(2), anywhere);
}
