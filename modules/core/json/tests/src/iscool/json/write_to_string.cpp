// SPDX-License-Identifier: Apache-2.0
#include <iscool/json/write_to_string.hpp>

#include <iscool/json/cast_int.hpp>
#include <iscool/json/cast_string.hpp>
#include <iscool/json/parse_string.hpp>

#include <gtest/gtest.h>

TEST(iscool_json_write_to_string, valid)
{
  Json::Value source_value;
  source_value["int"] = 24;
  source_value["object"]["property"] = "value";
  source_value["array"][0] = 10;
  source_value["array"][1] = 2;
  source_value["array"][2]["id"] = 72;
  source_value["array"][3] = 1.8;

  std::string str;

  EXPECT_TRUE(iscool::json::write_to_string(str, source_value));

  const Json::Value result(iscool::json::parse_string(str));

  EXPECT_EQ(24, iscool::json::cast<int>(result["int"]));
  EXPECT_EQ("value",
            iscool::json::cast<std::string>(result["object"]["property"]));

  ASSERT_EQ(Json::ArrayIndex(4), result["array"].size());
  EXPECT_EQ(10, iscool::json::cast<int>(result["array"][0]));
  EXPECT_EQ(2, iscool::json::cast<int>(result["array"][1]));
  EXPECT_EQ(72, iscool::json::cast<int>(result["array"][2]["id"]));
  EXPECT_EQ(1.8f, result["array"][3].asFloat());
}

TEST(iscool_json_write_to_string, compact)
{
  Json::Value source_value;
  source_value["array"][0] = 10;
  source_value["array"][1]["property"] = "value";
  source_value["array"][2] = 72;

  std::string str;

  EXPECT_TRUE(iscool::json::write_to_string(str, source_value));

  EXPECT_EQ(R"({"array":[10,{"property":"value"},72]})", str);
}

TEST(iscool_json_write_to_string, large_enough_output_is_not_reallocated)
{
  Json::Value source_value;
  source_value["array"][0] = 10;
  source_value["array"][1]["property"] = "value";
  source_value["array"][2] = 72;

  std::string str;
  str.reserve(1024);
  const char* const str_ptr = str.c_str();

  EXPECT_TRUE(iscool::json::write_to_string(str, source_value));

  EXPECT_EQ(str_ptr, str.c_str());
}
