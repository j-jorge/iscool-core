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
#include "iscool/style/json/to_declaration.h"

#include "iscool/json/parse_string.h"
#include "iscool/optional.impl.tpp"

#include "gtest/gtest.h"

class iscool_style_declaration_json_test : public ::testing::Test
{
public:
  iscool_style_declaration_json_test();

protected:
  Json::Value _value;
};

iscool_style_declaration_json_test::iscool_style_declaration_json_test()
  : _value(iscool::json::parse_string("{"
                                      "    \"uint\": 10,"
                                      "    \"int\": -4,"
                                      "    \"float\": 12.5,"
                                      "    \"string\": \"string\","
                                      "    \"bool\": true,"
                                      "    \"sub\": ["
                                      "        {"
                                      "          \"b\": false"
                                      "        },"
                                      "        {"
                                      "          \"member\": \"member\""
                                      "        }"
                                      "      ]"
                                      "}"))
{}

TEST_F(iscool_style_declaration_json_test, number_member)
{
  const iscool::style::declaration result(
      iscool::style::json::to_declaration(_value));
  EXPECT_TRUE(!!result.get_number("uint"));
  EXPECT_TRUE(!!result.get_number("int"));
  EXPECT_TRUE(!!result.get_number("float"));

  EXPECT_FALSE(!!result.get_number("string"));
  EXPECT_FALSE(!!result.get_number("bool"));
  EXPECT_FALSE(!!result.get_number("sub"));
}

TEST_F(iscool_style_declaration_json_test, string_member)
{
  const iscool::style::declaration result(
      iscool::style::json::to_declaration(_value));
  EXPECT_EQ("", result.get_string("uint", ""));
  EXPECT_EQ("", result.get_string("int", ""));
  EXPECT_EQ("", result.get_string("float", ""));
  EXPECT_NE("", result.get_string("string", ""));
  EXPECT_EQ("", result.get_string("bool", ""));
  EXPECT_EQ("", result.get_string("sub", ""));
}

TEST_F(iscool_style_declaration_json_test, boolean_member)
{
  const iscool::style::declaration result(
      iscool::style::json::to_declaration(_value));

  EXPECT_FALSE(!!result.get_boolean("uint"));
  EXPECT_FALSE(!!result.get_boolean("int"));
  EXPECT_FALSE(!!result.get_boolean("float"));
  EXPECT_FALSE(!!result.get_boolean("string"));
  EXPECT_TRUE(!!result.get_boolean("bool"));
  EXPECT_FALSE(!!result.get_boolean("sub"));
}

TEST_F(iscool_style_declaration_json_test, declaration_member)
{
  const iscool::style::declaration result(
      iscool::style::json::to_declaration(_value));

  EXPECT_FALSE(!!result.get_declaration("uint"));
  EXPECT_FALSE(!!result.get_declaration("int"));
  EXPECT_FALSE(!!result.get_declaration("float"));
  EXPECT_FALSE(!!result.get_declaration("string"));
  EXPECT_FALSE(!!result.get_declaration("bool"));
  EXPECT_TRUE(!!result.get_declaration("sub"));
}

TEST_F(iscool_style_declaration_json_test, number_values)
{
  const iscool::style::declaration result(
      iscool::style::json::to_declaration(_value));

  EXPECT_EQ(10.f, *result.get_number("uint"));
  EXPECT_EQ(-4.f, *result.get_number("int"));
  EXPECT_EQ(12.5f, *result.get_number("float"));
}

TEST_F(iscool_style_declaration_json_test, string_values)
{
  const iscool::style::declaration result(
      iscool::style::json::to_declaration(_value));

  EXPECT_EQ("string", result.get_string("string", ""));
  EXPECT_TRUE(!!result.get_string("string"));
  EXPECT_EQ("string", *result.get_string("string"));
}

TEST_F(iscool_style_declaration_json_test, boolean_values)
{
  const iscool::style::declaration result(
      iscool::style::json::to_declaration(_value));

  EXPECT_EQ(true, *result.get_boolean("bool"));
}

TEST_F(iscool_style_declaration_json_test, declaration_values)
{
  const iscool::style::declaration result(
      iscool::style::json::to_declaration(_value));

  const iscool::style::declaration inner(
      result.get_declaration_or_empty("sub"));

  EXPECT_EQ("member", inner.get_string("member", ""));
}

TEST_F(iscool_style_declaration_json_test, merged_declaration)
{
  const Json::Value other(
      iscool::json::parse_string("{"
                                 "    \"sub\": ["
                                 "        {"
                                 "          \"a\": 24,"
                                 "          \"member\": \"overwritten\""
                                 "        }"
                                 "     ]"
                                 "}"));

  iscool::style::declaration base(iscool::style::json::to_declaration(_value));
  base = base.merge(iscool::style::json::to_declaration(other));

  const iscool::style::declaration inner(base.get_declaration_or_empty("sub"));

  EXPECT_EQ("overwritten", inner.get_string("member", ""));
  EXPECT_EQ(24, inner.get_number("a", 0));
  EXPECT_FALSE(inner.get_boolean("b", true));
}

TEST_F(iscool_style_declaration_json_test, merged_with_path)
{
  const Json::Value other(
      iscool::json::parse_string("{"
                                 "    \"sub/a\": 24,"
                                 "    \"sub/member\": \"overwritten\","
                                 "    \"sub/extra\": \"more\""
                                 "}"));

  iscool::style::declaration base(iscool::style::json::to_declaration(_value));
  base = base.merge(iscool::style::json::to_declaration(other));

  const iscool::style::declaration inner(base.get_declaration_or_empty("sub"));

  EXPECT_EQ("overwritten", inner.get_string("member", ""));
  EXPECT_EQ("more", inner.get_string("extra", ""));
  EXPECT_EQ(24, inner.get_number("a", 0));
  EXPECT_FALSE(inner.get_boolean("b", true));
}

TEST_F(iscool_style_declaration_json_test, empty_declaration)
{
  const Json::Value json(iscool::json::parse_string("{"
                                                    "    \"sub\": []"
                                                    "}"));

  const iscool::style::declaration style(
      iscool::style::json::to_declaration(json));

  EXPECT_TRUE(!!style.get_declaration("sub"));
}
