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
#include "iscool/error/synopsis.h"

#include <gtest/gtest.h>

TEST(iscool_error_synopsis, getters)
{
  const iscool::error::synopsis synopsis(24, "a", "b", "c");

  EXPECT_EQ(std::size_t(24), synopsis.get_code());
  EXPECT_EQ("a", synopsis.get_category());
  EXPECT_EQ("b", synopsis.get_title());
  EXPECT_EQ("c", synopsis.get_message());
}
