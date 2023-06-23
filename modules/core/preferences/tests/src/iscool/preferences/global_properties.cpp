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
#include <iscool/preferences/declare_global_bool_property.hpp>
#include <iscool/preferences/declare_global_float_property.hpp>
#include <iscool/preferences/declare_global_int64_property.hpp>
#include <iscool/preferences/declare_global_string_property.hpp>
#include <iscool/preferences/get_global_bool_property.hpp>
#include <iscool/preferences/get_global_float_property.hpp>
#include <iscool/preferences/get_global_int64_property.hpp>
#include <iscool/preferences/get_global_string_property.hpp>
#include <iscool/preferences/set_global_properties.hpp>

#include <gtest/gtest.h>

TEST(iscool_preferences, global_properties)
{
  const iscool::preferences::bool_property bool_property(
      iscool::preferences::declare_global_bool_property("bool", true));
  const iscool::preferences::float_property float_property(
      iscool::preferences::declare_global_float_property("float", 11));
  const iscool::preferences::int64_property int64_property(
      iscool::preferences::declare_global_int64_property("int64", 111));
  const iscool::preferences::string_property string_property(
      iscool::preferences::declare_global_string_property("string", "abc"));

  EXPECT_TRUE(iscool::preferences::get_global_bool_property(bool_property));
  EXPECT_FLOAT_EQ(
      11, iscool::preferences::get_global_float_property(float_property));
  EXPECT_EQ(111,
            iscool::preferences::get_global_int64_property(int64_property));
  EXPECT_EQ("abc",
            iscool::preferences::get_global_string_property(string_property));

  iscool::preferences::set_global_properties({ { "bool", "0" },
                                               { "float", "2.2" },
                                               { "int64", "-222" },
                                               { "string", "ABC" } });

  EXPECT_FALSE(iscool::preferences::get_global_bool_property(bool_property));
  EXPECT_FLOAT_EQ(
      2.2, iscool::preferences::get_global_float_property(float_property));
  EXPECT_EQ(-222,
            iscool::preferences::get_global_int64_property(int64_property));
  EXPECT_EQ("ABC",
            iscool::preferences::get_global_string_property(string_property));
}

TEST(iscool_preferences, property_declared_after_globals_are_set)
{
  iscool::preferences::set_global_properties({ { "bool", "0" },
                                               { "float", "2.2" },
                                               { "int64", "-222" },
                                               { "string", "ABC" } });

  const iscool::preferences::bool_property bool_property(
      iscool::preferences::declare_global_bool_property("bool", true));
  const iscool::preferences::float_property float_property(
      iscool::preferences::declare_global_float_property("float", 11));
  const iscool::preferences::int64_property int64_property(
      iscool::preferences::declare_global_int64_property("int64", 111));
  const iscool::preferences::string_property string_property(
      iscool::preferences::declare_global_string_property("string", "abc"));

  EXPECT_FALSE(iscool::preferences::get_global_bool_property(bool_property));
  EXPECT_FLOAT_EQ(
      2.2, iscool::preferences::get_global_float_property(float_property));
  EXPECT_EQ(-222,
            iscool::preferences::get_global_int64_property(int64_property));
  EXPECT_EQ("ABC",
            iscool::preferences::get_global_string_property(string_property));
}
