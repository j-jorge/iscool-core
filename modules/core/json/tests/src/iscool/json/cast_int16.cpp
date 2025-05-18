// SPDX-License-Identifier: Apache-2.0
#include <iscool/json/bad_cast.hpp>
#include <iscool/json/cast_int16.hpp>
#include <iscool/json/is_of_type_int16.hpp>

#include <json/value.h>

#include "gtest/gtest.h"

TEST(iscool_json_cast, to_int16)
{
  Json::Value value0(0);
  EXPECT_EQ(0, iscool::json::cast<std::int16_t>(value0));

  Json::Value value1(-100);
  EXPECT_EQ(-100, iscool::json::cast<std::int16_t>(value1));

  Json::Value value2(10000);
  EXPECT_EQ(10000, iscool::json::cast<std::int16_t>(value2));

  Json::Value value3(std::int16_t(-32768));
  EXPECT_EQ(std::int16_t(-32768), iscool::json::cast<std::int16_t>(value3));

  Json::Value value4(std::int16_t(32767));
  EXPECT_EQ(std::int16_t(32767), iscool::json::cast<std::int16_t>(value4));
}

TEST(iscool_json_cast, is_of_type_int16)
{
  Json::Value value0(0);
  EXPECT_TRUE(iscool::json::is_of_type<std::int16_t>(value0));

  Json::Value value1(-100);
  EXPECT_TRUE(iscool::json::is_of_type<std::int16_t>(value1));

  Json::Value value2(10000);
  EXPECT_TRUE(iscool::json::is_of_type<std::int16_t>(value2));

  Json::Value value3(-32768);
  EXPECT_TRUE(iscool::json::is_of_type<std::int16_t>(value3));

  Json::Value value4(std::int16_t(32767));
  EXPECT_TRUE(iscool::json::is_of_type<std::int16_t>(value4));
}

TEST(iscool_json_cast, is_not_of_type_int16)
{
  Json::Value value;
  EXPECT_FALSE(iscool::json::is_of_type<std::int16_t>(value));

  Json::Value value0("10");
  EXPECT_FALSE(iscool::json::is_of_type<std::int16_t>(value0));

  Json::Value value1(true);
  EXPECT_FALSE(iscool::json::is_of_type<std::int16_t>(value1));

  Json::Value value2(Json::arrayValue);
  EXPECT_FALSE(iscool::json::is_of_type<std::int16_t>(value2));

  Json::Value value3(Json::objectValue);
  EXPECT_FALSE(iscool::json::is_of_type<std::int16_t>(value3));

  Json::Value value4(40000);
  EXPECT_FALSE(iscool::json::is_of_type<std::int16_t>(value4));

  Json::Value value5(-40000);
  EXPECT_FALSE(iscool::json::is_of_type<std::int16_t>(value5));
}

TEST(iscool_json_cast, to_int16_throw)
{
  Json::Value value;
  EXPECT_THROW(iscool::json::cast<std::int16_t>(value),
               iscool::json::bad_cast);

  Json::Value value0("10");
  EXPECT_THROW(iscool::json::cast<std::int16_t>(value0),
               iscool::json::bad_cast);

  Json::Value value1(true);
  EXPECT_THROW(iscool::json::cast<std::int16_t>(value1),
               iscool::json::bad_cast);

  Json::Value value2(Json::arrayValue);
  EXPECT_THROW(iscool::json::cast<std::int16_t>(value2),
               iscool::json::bad_cast);

  Json::Value value3(Json::objectValue);
  EXPECT_THROW(iscool::json::cast<std::int16_t>(value3),
               iscool::json::bad_cast);
}

TEST(iscool_json_cast, to_int16_fallback)
{
  EXPECT_EQ(94, iscool::json::cast<std::int16_t>(Json::Value(), 94));
  EXPECT_EQ(49, iscool::json::cast<std::int16_t>(Json::Value(), 49));
  EXPECT_EQ(
      9, iscool::json::cast<std::int16_t>(Json::Value(std::int16_t(9)), 49));
}
