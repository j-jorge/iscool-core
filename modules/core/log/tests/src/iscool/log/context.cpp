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
#include <iscool/log/context.hpp>

#include <gtest/gtest.h>

TEST(iscool_log_context, getters)
{
  const iscool::log::context context("reporter", "origin", "file", 89);

  EXPECT_EQ("reporter", context.get_reporter());
  EXPECT_EQ("origin", context.get_origin());
  EXPECT_EQ("file", context.get_file());
  EXPECT_EQ(89, context.get_line());
}

TEST(iscool_log_context, copy)
{
  const iscool::log::context context("rp", "or", "f", 222);
  const iscool::log::context copy(context);

  EXPECT_EQ(context.get_reporter(), copy.get_reporter());
  EXPECT_EQ(context.get_origin(), copy.get_origin());
  EXPECT_EQ(context.get_file(), copy.get_file());
  EXPECT_EQ(context.get_line(), copy.get_line());
}

TEST(iscool_log_context, assignment)
{
  iscool::log::context copy;

  const iscool::log::context context("rp", "or", "f", 222);

  copy = context;

  EXPECT_EQ(context.get_reporter(), copy.get_reporter());
  EXPECT_EQ(context.get_origin(), copy.get_origin());
  EXPECT_EQ(context.get_file(), copy.get_file());
  EXPECT_EQ(context.get_line(), copy.get_line());
}
