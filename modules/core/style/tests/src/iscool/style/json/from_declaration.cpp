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
#include "gtest/gtest.h"

#include <iscool/style/declaration.hpp>
#include <iscool/style/json/from_declaration.hpp>

#include <iscool/json/cast_bool.hpp>
#include <iscool/json/cast_float.hpp>
#include <iscool/json/cast_string.hpp>
#include <iscool/json/is_member.hpp>
#include <iscool/json/is_of_type_bool.hpp>
#include <iscool/json/is_of_type_float.hpp>
#include <iscool/json/is_of_type_string.hpp>

class iscool_style_from_declaration_json_test : public ::testing::Test
{
public:
  iscool_style_from_declaration_json_test();

protected:
  iscool::style::declaration _style;
};

iscool_style_from_declaration_json_test ::
    iscool_style_from_declaration_json_test()
{
  // all numbers are stored in float
  _style.set_number("float", 12.5f);
  _style.set_string("string", "string");
  _style.set_boolean("bool", true);

  iscool::style::declaration sub;
  sub.set_boolean("b", false);
  sub.set_string("member", "member");

  _style.set_declaration("sub", sub);
}

TEST_F(iscool_style_from_declaration_json_test, number_member)
{
  const Json::Value result(iscool::style::json::from_declaration(_style));
  EXPECT_TRUE(iscool::json::is_member("float", result));
  EXPECT_TRUE(iscool::json::is_of_type<float>(result["float"]));
}

TEST_F(iscool_style_from_declaration_json_test, string_member)
{
  const Json::Value result(iscool::style::json::from_declaration(_style));
  EXPECT_TRUE(iscool::json::is_member("string", result));
  EXPECT_TRUE(iscool::json::is_of_type<std::string>(result["string"]));
}

TEST_F(iscool_style_from_declaration_json_test, boolean_member)
{
  const Json::Value result(iscool::style::json::from_declaration(_style));
  EXPECT_TRUE(iscool::json::is_member("bool", result));
  EXPECT_TRUE(iscool::json::is_of_type<bool>(result["bool"]));
}

TEST_F(iscool_style_from_declaration_json_test, declaration_member)
{
  const Json::Value result(iscool::style::json::from_declaration(_style));
  EXPECT_TRUE(iscool::json::is_member("sub", result));

  const Json::Value inner(result["sub"]);
  EXPECT_TRUE(inner.isArray());
  EXPECT_EQ(std::size_t(1), inner.size());

  const Json::Value inner_style(inner[0]);
  EXPECT_TRUE(inner_style.isObject());
  EXPECT_TRUE(iscool::json::is_member("b", inner_style));
  EXPECT_TRUE(iscool::json::is_member("member", inner_style));
  EXPECT_TRUE(iscool::json::is_of_type<bool>(inner_style["b"]));
  EXPECT_TRUE(iscool::json::is_of_type<std::string>(inner_style["member"]));
}

TEST_F(iscool_style_from_declaration_json_test, number_values)
{
  const Json::Value result(iscool::style::json::from_declaration(_style));
  EXPECT_EQ(12.5f, iscool::json::cast<float>(result["float"], 0.0f));
}

TEST_F(iscool_style_from_declaration_json_test, string_values)
{
  const Json::Value result(iscool::style::json::from_declaration(_style));
  EXPECT_EQ("string", iscool::json::cast<std::string>(result["string"], ""));
}

TEST_F(iscool_style_from_declaration_json_test, boolean_values)
{
  const Json::Value result(iscool::style::json::from_declaration(_style));
  EXPECT_TRUE(iscool::json::cast<bool>(result["bool"], false));
}

TEST_F(iscool_style_from_declaration_json_test, declaration_values)
{
  const Json::Value result(iscool::style::json::from_declaration(_style));
  const Json::Value inner(result["sub"][0]);

  EXPECT_FALSE(iscool::json::cast<bool>(inner["b"], true));
  EXPECT_EQ("member", iscool::json::cast<std::string>(inner["member"], ""));
}

TEST_F(iscool_style_from_declaration_json_test, merged_declaration)
{
  iscool::style::declaration other;
  iscool::style::declaration sub;
  sub.set_number("a", 24.0f);
  sub.set_string("member", "overwritten");
  other.set_declaration("sub", sub);

  iscool::style::declaration merged(_style.merge(other));
  const Json::Value result(iscool::style::json::from_declaration(merged));

  const Json::Value inner(result["sub"][0]);

  EXPECT_TRUE(iscool::json::is_member("a", inner));
  EXPECT_TRUE(iscool::json::is_of_type<float>(inner["a"]));
  EXPECT_EQ(24.0f, iscool::json::cast<float>(inner["a"], 0));
  EXPECT_EQ("overwritten",
            iscool::json::cast<std::string>(inner["member"], ""));
}
