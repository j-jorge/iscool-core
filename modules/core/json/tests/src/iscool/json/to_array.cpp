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
#include "iscool/json/to_array.h"
#include "iscool/json/cast_int.h"

#include <list>

#include <gtest/gtest.h>

TEST(iscool_json_to_vector, vector_of_ints)
{
  const std::vector<int> v({ 3, 1, 2 });
  const Json::Value result(iscool::json::to_array(v.begin(), v.end()));

  EXPECT_TRUE(result.isArray());
  EXPECT_EQ(3, result.size());

  EXPECT_EQ(3, iscool::json::cast<int>(result[0]));
  EXPECT_EQ(1, iscool::json::cast<int>(result[1]));
  EXPECT_EQ(2, iscool::json::cast<int>(result[2]));
}

TEST(iscool_json_to_vector, list_of_ints)
{
  const std::list<int> v({ 21, 92 });
  const Json::Value result(iscool::json::to_array(v.begin(), v.end()));

  EXPECT_TRUE(result.isArray());
  EXPECT_EQ(2, result.size());

  EXPECT_EQ(21, iscool::json::cast<int>(result[0]));
  EXPECT_EQ(92, iscool::json::cast<int>(result[1]));
}

TEST(iscool_json_to_vector, vector_of_strings)
{
  const std::vector<std::string> v({ "a", "", "bc", "e" });
  const Json::Value result(iscool::json::to_array(v.begin(), v.end()));

  EXPECT_TRUE(result.isArray());
  EXPECT_EQ(4, result.size());

  EXPECT_EQ("a", iscool::json::cast<std::string>(result[0]));
  EXPECT_EQ("", iscool::json::cast<std::string>(result[1]));
  EXPECT_EQ("bc", iscool::json::cast<std::string>(result[2]));
  EXPECT_EQ("e", iscool::json::cast<std::string>(result[3]));
}
