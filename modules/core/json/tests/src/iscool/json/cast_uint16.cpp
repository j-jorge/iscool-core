// SPDX-License-Identifier: Apache-2.0
#include <iscool/json/bad_cast.hpp>
#include <iscool/json/cast_uint16.hpp>
#include <iscool/json/is_of_type_uint16.hpp>

#include <json/value.h>

#include <gtest/gtest.h>

TEST(iscool_json_cast, to_uint16)
{
  const Json::Value value0(0);
  EXPECT_EQ(std::uint16_t(0), iscool::json::cast<std::uint16_t>(value0));

  const Json::Value value2(100);
  EXPECT_EQ(std::uint16_t(100), iscool::json::cast<std::uint16_t>(value2));

  const Json::Value value5(std::uint16_t(65535));
  EXPECT_EQ(std::uint16_t(65535), iscool::json::cast<std::uint16_t>(value5));
}

TEST(iscool_json_cast, is_of_type_uint16)
{
  const Json::Value value0(0);
  EXPECT_TRUE(iscool::json::is_of_type<std::uint16_t>(value0));

  const Json::Value value2(100);
  EXPECT_TRUE(iscool::json::is_of_type<std::uint16_t>(value2));

  const Json::Value value5(std::uint16_t(65535));
  EXPECT_TRUE(iscool::json::is_of_type<std::uint16_t>(value5));
}

TEST(iscool_json_cast, is_not_of_type_uint16)
{
  const Json::Value value;
  EXPECT_FALSE(iscool::json::is_of_type<std::uint16_t>(value));

  const Json::Value value0("10");
  EXPECT_FALSE(iscool::json::is_of_type<std::uint16_t>(value0));

  const Json::Value value1(true);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint16_t>(value1));

  const Json::Value value2(Json::arrayValue);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint16_t>(value2));

  const Json::Value value3(Json::objectValue);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint16_t>(value3));

  const Json::Value value4(-100);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint16_t>(value4));

  const Json::Value value5(-123456789);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint16_t>(value5));

  const Json::Value value6(std::int64_t(-1234567890123456));
  EXPECT_FALSE(iscool::json::is_of_type<std::uint16_t>(value6));

  const Json::Value value7(5.4f);
  EXPECT_FALSE(iscool::json::is_of_type<std::uint16_t>(value7));
}

TEST(iscool_json_cast, to_uint16_throw)
{
  const Json::Value value;
  EXPECT_THROW(iscool::json::cast<std::uint16_t>(value),
               iscool::json::bad_cast);

  const Json::Value value0("10");
  EXPECT_THROW(iscool::json::cast<std::uint16_t>(value0),
               iscool::json::bad_cast);

  const Json::Value value1(true);
  EXPECT_THROW(iscool::json::cast<std::uint16_t>(value1),
               iscool::json::bad_cast);

  const Json::Value value2(Json::arrayValue);
  EXPECT_THROW(iscool::json::cast<std::uint16_t>(value2),
               iscool::json::bad_cast);

  const Json::Value value3(Json::objectValue);
  EXPECT_THROW(iscool::json::cast<std::uint16_t>(value3),
               iscool::json::bad_cast);

  const Json::Value value4(-100);
  EXPECT_THROW(iscool::json::cast<std::uint16_t>(value4),
               iscool::json::bad_cast);

  const Json::Value value5(-123456789);
  EXPECT_THROW(iscool::json::cast<std::uint16_t>(value5),
               iscool::json::bad_cast);

  const Json::Value value6(std::int64_t(-1234567890123456));
  EXPECT_THROW(iscool::json::cast<std::uint16_t>(value6),
               iscool::json::bad_cast);

  const Json::Value value7(5.4f);
  EXPECT_THROW(iscool::json::cast<std::uint16_t>(value7),
               iscool::json::bad_cast);
}

TEST(iscool_json_cast, to_uint16_fallback)
{
  EXPECT_EQ(123, iscool::json::cast<std::uint16_t>(Json::Value(), 123));
  EXPECT_EQ(24, iscool::json::cast<std::uint16_t>(Json::Value(), 24));
  EXPECT_EQ(std::uint16_t(65535),
            iscool::json::cast<std::uint16_t>(Json::Value(65535), 23));
}
