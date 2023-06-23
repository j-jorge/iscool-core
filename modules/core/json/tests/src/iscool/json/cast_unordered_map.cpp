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
#include "iscool/json/cast_unordered_map.h"
#include "iscool/json/bad_cast.h"
#include "iscool/json/cast_int.h"
#include "iscool/json/cast_string.h"
#include "iscool/json/is_of_type_array.h"

#include "gtest/gtest.h"

TEST(iscool_json_cast, to_unordered_map)
{
  Json::Value value0;
  value0[0]["key"] = 1;
  value0[0]["value"] = "abc";
  value0[1]["key"] = 2;
  value0[1]["value"] = "def";

  typedef std::unordered_map<int, std::string> map_t;
  const map_t expected({ { 1, "abc" }, { 2, "def" } });
  EXPECT_EQ(expected, iscool::json::cast<map_t>(value0));
}

TEST(iscool_json_cast, is_of_type_unordered_map)
{
  typedef std::unordered_map<int, std::string> map_t;

  Json::Value value0;
  value0[0]["key"] = 1;
  value0[0]["value"] = "abc";
  value0[1]["key"] = 2;
  value0[1]["value"] = "def";

  EXPECT_TRUE(iscool::json::is_of_type<map_t>(value0));
}

TEST(iscool_json_cast, is_not_of_type_unordered_map)
{
  typedef std::unordered_map<int, std::string> map_t;

  Json::Value value;
  EXPECT_FALSE(iscool::json::is_of_type<map_t>(value));

  Json::Value value0("10");
  EXPECT_FALSE(iscool::json::is_of_type<map_t>(value0));

  Json::Value value1(std::uint64_t(0x123456789abcdef));
  EXPECT_FALSE(iscool::json::is_of_type<map_t>(value1));

  Json::Value value2(Json::objectValue);
  EXPECT_FALSE(iscool::json::is_of_type<map_t>(value2));

  Json::Value value3(5.4f);
  EXPECT_FALSE(iscool::json::is_of_type<map_t>(value3));

  Json::Value value4(-10);
  EXPECT_FALSE(iscool::json::is_of_type<map_t>(value4));

  Json::Value value5;
  value5[0]["key"] = 1.5;
  value5[0]["value"] = "abc";
  EXPECT_FALSE(iscool::json::is_of_type<map_t>(value5));

  Json::Value value6;
  value6[0]["eky"] = 1;
  value6[0]["avlue"] = "abc";
  EXPECT_FALSE(iscool::json::is_of_type<map_t>(value6));
}

TEST(iscool_json_cast, to_unordered_map_throw)
{
  typedef std::unordered_map<int, std::string> map_t;

  Json::Value value;
  EXPECT_THROW(iscool::json::cast<map_t>(value), iscool::json::bad_cast);

  Json::Value value0("10");
  EXPECT_THROW(iscool::json::cast<map_t>(value0), iscool::json::bad_cast);

  Json::Value value1(std::uint64_t(0x123456789abcdef));
  EXPECT_THROW(iscool::json::cast<map_t>(value1), iscool::json::bad_cast);

  Json::Value value2(Json::objectValue);
  EXPECT_THROW(iscool::json::cast<map_t>(value2), iscool::json::bad_cast);

  Json::Value value3(5.4f);
  EXPECT_THROW(iscool::json::cast<map_t>(value3), iscool::json::bad_cast);

  Json::Value value4(-10);
  EXPECT_THROW(iscool::json::cast<map_t>(value4), iscool::json::bad_cast);

  Json::Value value5;
  value5[0]["key"] = 1.5;
  value5[0]["value"] = "abc";
  EXPECT_THROW(iscool::json::cast<map_t>(value5), iscool::json::bad_cast);

  Json::Value value6;
  value6[0]["eky"] = 1;
  value6[0]["avlue"] = "abc";
  EXPECT_THROW(iscool::json::cast<map_t>(value6), iscool::json::bad_cast);
}

TEST(iscool_json_cast, to_unordered_map_fallback)
{
  typedef std::unordered_map<std::string, int> map_t;

  const map_t expected_1({ { "abc", 0 }, { "c", 9 } });
  EXPECT_EQ(expected_1, iscool::json::cast<map_t>(Json::Value(), expected_1));

  const map_t expected_2({ { "18", 90 }, { "fourty-four", 44 } });
  EXPECT_EQ(expected_2, iscool::json::cast<map_t>(Json::Value(), expected_2));

  Json::Value value;
  value[0]["key"] = "one";
  value[0]["value"] = 1;
  value[1]["key"] = "two";
  value[1]["value"] = 2;

  const map_t expected_3({ { "one", 1 }, { "two", 2 } });
  EXPECT_EQ(expected_3, iscool::json::cast<map_t>(value, expected_2));
}
