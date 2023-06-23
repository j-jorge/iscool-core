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
#include <iscool/json/bad_cast.hpp>
#include <iscool/json/cast_string.hpp>
#include <iscool/json/is_of_type_string.hpp>

#include <json/value.h>

#include "gtest/gtest.h"

TEST(iscool_json_cast, to_string)
{
  Json::Value value0("Bonjour");
  EXPECT_EQ("Bonjour", iscool::json::cast<std::string>(value0));

  Json::Value value1(std::string("Bonjour"));
  EXPECT_EQ("Bonjour", iscool::json::cast<std::string>(value1));

  Json::Value value2("");
  EXPECT_EQ("", iscool::json::cast<std::string>(value2));

  const char* const str = "constchar*";
  Json::Value value3(str);
  EXPECT_EQ(str, iscool::json::cast<std::string>(value3));

  Json::Value value4("true");
  EXPECT_EQ("true", iscool::json::cast<std::string>(value4));
}

TEST(iscool_json_cast, is_of_type_string)
{
  Json::Value value0("Bonjour");
  EXPECT_TRUE(iscool::json::is_of_type<std::string>(value0));

  Json::Value value1(std::string("Bonjour"));
  EXPECT_TRUE(iscool::json::is_of_type<std::string>(value1));

  Json::Value value2("");
  EXPECT_TRUE(iscool::json::is_of_type<std::string>(value2));

  const char* const str = "constchar*";
  Json::Value value3(str);
  EXPECT_TRUE(iscool::json::is_of_type<std::string>(value3));

  Json::Value value4("true");
  EXPECT_TRUE(iscool::json::is_of_type<std::string>(value4));
}

TEST(iscool_json_cast, is_not_of_type_string)
{
  Json::Value value0(5u);
  EXPECT_FALSE(iscool::json::is_of_type<std::string>(value0));

  Json::Value value1(5.0f);
  EXPECT_FALSE(iscool::json::is_of_type<std::string>(value1));

  Json::Value value2(true);
  EXPECT_FALSE(iscool::json::is_of_type<std::string>(value2));

  Json::Value value3(-15);
  EXPECT_FALSE(iscool::json::is_of_type<std::string>(value3));

  Json::Value value4(Json::arrayValue);
  EXPECT_FALSE(iscool::json::is_of_type<std::string>(value4));

  Json::Value value5(Json::objectValue);
  EXPECT_FALSE(iscool::json::is_of_type<std::string>(value5));
}

TEST(iscool_json_cast, to_string_throw)
{
  Json::Value value0(5u);
  EXPECT_THROW(iscool::json::cast<std::string>(value0),
               iscool::json::bad_cast);

  Json::Value value1(5.0f);
  EXPECT_THROW(iscool::json::cast<std::string>(value1),
               iscool::json::bad_cast);

  Json::Value value2(true);
  EXPECT_THROW(iscool::json::cast<std::string>(value2),
               iscool::json::bad_cast);

  Json::Value value3(-15);
  EXPECT_THROW(iscool::json::cast<std::string>(value3),
               iscool::json::bad_cast);

  Json::Value value4(Json::arrayValue);
  EXPECT_THROW(iscool::json::cast<std::string>(value4),
               iscool::json::bad_cast);

  Json::Value value5(Json::objectValue);
  EXPECT_THROW(iscool::json::cast<std::string>(value5),
               iscool::json::bad_cast);
}

TEST(iscool_json_cast, to_string_fallback)
{
  EXPECT_EQ("fallback",
            iscool::json::cast<std::string>(Json::Value(), "fallback"));
  EXPECT_EQ("ballfack",
            iscool::json::cast<std::string>(Json::Value(), "ballfack"));
  EXPECT_EQ("ok", iscool::json::cast<std::string>(Json::Value("ok"), "no"));
}
