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
#include "iscool/json/cast_uint64.h"
#include "iscool/json/bad_cast.h"
#include "iscool/json/is_of_type_uint64.h"

#include <json/value.h>

#include "gtest/gtest.h"

TEST(iscool_json_cast, to_uint64)
{
  Json::Value value0(0);
  EXPECT_EQ(std::uint64_t(0), iscool::json::cast<std::uint64_t>(value0));

  Json::Value value2(10000);
  EXPECT_EQ(std::uint64_t(10000), iscool::json::cast<std::uint64_t>(value2));

  Json::Value value5(std::uint64_t(51234567890123456));
  EXPECT_EQ(std::uint64_t(51234567890123456),
            iscool::json::cast<std::uint64_t>(value5));
}

TEST(iscool_json_cast, is_of_type_uint64)
{
  Json::Value value0(0);
  EXPECT_TRUE(iscool::json::is_of_type<std::uint64_t>(value0));

  Json::Value value2(10000);
  EXPECT_TRUE(iscool::json::is_of_type<std::uint64_t>(value2));

  Json::Value value5(std::uint64_t(51234567890123456));
  EXPECT_TRUE(iscool::json::is_of_type<std::uint64_t>(value5));
}

TEST(iscool_json_cast, is_not_of_type_uint64)
{
  Json::Value value;
  EXPECT_FALSE(iscool::json::is_of_type<std::uint64_t>(value));

  Json::Value value0("10");
  EXPECT_FALSE(iscool::json::is_of_type<std::uint64_t>(value0));

  Json::Value value1(true);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint64_t>(value1));

  Json::Value value2(Json::arrayValue);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint64_t>(value2));

  Json::Value value3(Json::objectValue);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint64_t>(value3));

  Json::Value value4(-100);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint64_t>(value4));

  Json::Value value5(-123456789);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint64_t>(value5));

  Json::Value value6(std::int64_t(-1234567890123456));
  EXPECT_FALSE(iscool::json::is_of_type<std::uint64_t>(value6));

  Json::Value value7(5.4f);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint64_t>(value7));
}

TEST(iscool_json_cast, to_uint64_throw)
{
  Json::Value value;
  EXPECT_THROW(iscool::json::cast<std::uint64_t>(value),
               iscool::json::bad_cast);

  Json::Value value0("10");
  EXPECT_THROW(iscool::json::cast<std::uint64_t>(value0),
               iscool::json::bad_cast);

  Json::Value value1(true);
  EXPECT_THROW(iscool::json::cast<std::uint64_t>(value1),
               iscool::json::bad_cast);

  Json::Value value2(Json::arrayValue);
  EXPECT_THROW(iscool::json::cast<std::uint64_t>(value2),
               iscool::json::bad_cast);

  Json::Value value3(Json::objectValue);
  EXPECT_THROW(iscool::json::cast<std::uint64_t>(value3),
               iscool::json::bad_cast);

  Json::Value value4(-100);
  EXPECT_THROW(iscool::json::cast<std::uint64_t>(value4),
               iscool::json::bad_cast);

  Json::Value value5(-123456789);
  EXPECT_THROW(iscool::json::cast<std::uint64_t>(value5),
               iscool::json::bad_cast);

  Json::Value value6(std::int64_t(-1234567890123456));
  EXPECT_THROW(iscool::json::cast<std::uint64_t>(value6),
               iscool::json::bad_cast);

  Json::Value value7(5.4f);
  EXPECT_THROW(iscool::json::cast<std::uint64_t>(value7),
               iscool::json::bad_cast);
}

TEST(iscool_json_cast, to_uint64_fallback)
{
  EXPECT_EQ(984, iscool::json::cast<std::uint64_t>(Json::Value(), 984));
  EXPECT_EQ(894, iscool::json::cast<std::uint64_t>(Json::Value(), 894));
  EXPECT_EQ(std::uint64_t(51234567890123456),
            iscool::json::cast<std::uint64_t>(
                Json::Value(std::uint64_t(51234567890123456)), 894));
}
