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
#include <iscool/json/cast_int.hpp>
#include <iscool/json/cast_string.hpp>
#include <iscool/json/parse_stream.hpp>

#include "gtest/gtest.h"

TEST(iscool_json_parse_stream, parse_stream_valid)
{
  std::istringstream iss("{"
                         "  \"int\": 24,"
                         "  \"object\": { \"property\": \"value\" },"
                         "  \"array\": [ 10, 2, { \"id\": 72 }, 1.8 ]"
                         "}");

  Json::Value value(iscool::json::parse_stream(iss));

  EXPECT_EQ(24, iscool::json::cast<int>(value["int"]));
  EXPECT_EQ("value",
            iscool::json::cast<std::string>(value["object"]["property"]));

  ASSERT_EQ(Json::ArrayIndex(4), value["array"].size());
  EXPECT_EQ(10, iscool::json::cast<int>(value["array"][0]));
  EXPECT_EQ(2, iscool::json::cast<int>(value["array"][1]));
  EXPECT_EQ(72, iscool::json::cast<int>(value["array"][2]["id"]));
  EXPECT_EQ(1.8f, value["array"][3].asFloat());
}

TEST(iscool_json_parse_stream, parse_stream_invalid)
{
  std::istringstream iss("Not a valid Json.");
  Json::Value value(iscool::json::parse_stream(iss));

  EXPECT_TRUE(value.isNull());
}

TEST(iscool_json_parse_stream, parse_stream_empty)
{
  std::istringstream iss("");
  Json::Value value(iscool::json::parse_stream(iss));

  EXPECT_TRUE(value.isNull());
}

TEST(iscool_json_parse_stream, parse_stream_array)
{
  std::istringstream iss("[ 1, 2, 3 ]");
  Json::Value value(iscool::json::parse_stream(iss));

  EXPECT_EQ(Json::arrayValue, value.type());
  ASSERT_EQ(Json::ArrayIndex(3), value.size());
  EXPECT_EQ(1, iscool::json::cast<int>(value[0]));
  EXPECT_EQ(2, iscool::json::cast<int>(value[1]));
  EXPECT_EQ(3, iscool::json::cast<int>(value[2]));
}
