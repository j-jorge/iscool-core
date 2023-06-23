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
#include "iscool/json/cast_double.h"
#include "iscool/json/bad_cast.h"
#include "iscool/json/is_of_type_double.h"

#include <json/value.h>

#include "gtest/gtest.h"

TEST(iscool_json_cast, to_double)
{
  Json::Value value0(0.0f);
  EXPECT_FLOAT_EQ(0.0, iscool::json::cast<double>(value0));

  Json::Value value1(100.0f);
  EXPECT_FLOAT_EQ(100.0, iscool::json::cast<double>(value1));

  Json::Value value2(10000.0f);
  EXPECT_FLOAT_EQ(10000.0, iscool::json::cast<double>(value2));

  Json::Value value3(12345.6789f);
  EXPECT_FLOAT_EQ(12345.6789, iscool::json::cast<double>(value3));

  Json::Value value4(10);
  EXPECT_FLOAT_EQ(10.0, iscool::json::cast<double>(value4));

  Json::Value value5(-10);
  EXPECT_DOUBLE_EQ(-10.0, iscool::json::cast<double>(value5));

  Json::Value value6(std::uint64_t(10));
  EXPECT_DOUBLE_EQ(10.0, iscool::json::cast<double>(value6));

  Json::Value value7(10u);
  EXPECT_DOUBLE_EQ(10.0, iscool::json::cast<double>(value7));

  Json::Value value8(static_cast<double>(5.0));
  EXPECT_DOUBLE_EQ(5.0, iscool::json::cast<double>(value8));

  Json::Value value9(10.0);
  EXPECT_DOUBLE_EQ(10.0, iscool::json::cast<double>(value9));
}

TEST(iscool_json_cast, is_of_type_double)
{
  Json::Value value0(0.0f);
  EXPECT_TRUE(iscool::json::is_of_type<double>(value0));

  Json::Value value1(100.0f);
  EXPECT_TRUE(iscool::json::is_of_type<double>(value1));

  Json::Value value2(10000.0f);
  EXPECT_TRUE(iscool::json::is_of_type<double>(value2));

  Json::Value value3(12345.6789f);
  EXPECT_TRUE(iscool::json::is_of_type<double>(value3));

  Json::Value value4(10);
  EXPECT_TRUE(iscool::json::is_of_type<double>(value4));

  Json::Value value5(-10);
  EXPECT_TRUE(iscool::json::is_of_type<double>(value5));

  Json::Value value6(std::uint64_t(10));
  EXPECT_TRUE(iscool::json::is_of_type<double>(value6));

  Json::Value value7(10u);
  EXPECT_TRUE(iscool::json::is_of_type<double>(value7));

  Json::Value value8(double(5.0));
  EXPECT_TRUE(iscool::json::is_of_type<double>(value8));

  Json::Value value9(10.0);
  EXPECT_TRUE(iscool::json::is_of_type<double>(value9));
}

TEST(iscool_json_cast, is_not_of_type_double)
{
  Json::Value value;
  EXPECT_FALSE(iscool::json::is_of_type<double>(value));

  Json::Value value0("10");
  EXPECT_FALSE(iscool::json::is_of_type<double>(value0));

  Json::Value value1(true);
  EXPECT_FALSE(iscool::json::is_of_type<double>(value1));

  Json::Value value2(Json::arrayValue);
  EXPECT_FALSE(iscool::json::is_of_type<double>(value2));

  Json::Value value3(Json::objectValue);
  EXPECT_FALSE(iscool::json::is_of_type<double>(value3));
}

TEST(iscool_json_cast, to_double_throw)
{
  Json::Value value;
  EXPECT_THROW(iscool::json::cast<double>(value), iscool::json::bad_cast);

  Json::Value value0("10");
  EXPECT_THROW(iscool::json::cast<double>(value0), iscool::json::bad_cast);

  Json::Value value1(true);
  EXPECT_THROW(iscool::json::cast<double>(value1), iscool::json::bad_cast);

  Json::Value value2(Json::arrayValue);
  EXPECT_THROW(iscool::json::cast<double>(value2), iscool::json::bad_cast);

  Json::Value value3(Json::objectValue);
  EXPECT_THROW(iscool::json::cast<double>(value3), iscool::json::bad_cast);
}

TEST(iscool_json_cast, to_double_fallback)
{
  EXPECT_DOUBLE_EQ(84.9, iscool::json::cast<double>(Json::Value(), 84.9));
  EXPECT_DOUBLE_EQ(8.49, iscool::json::cast<double>(Json::Value(), 8.49));
  EXPECT_DOUBLE_EQ(1, iscool::json::cast<double>(Json::Value(1.0), 8.0));
}
