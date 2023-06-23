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
#include "iscool/json/is_member.h"

#include "gtest/gtest.h"

TEST(iscool_json_is_member, check_member_is_true)
{
  Json::Value value;
  value["member"] = 0;

  ASSERT_TRUE(iscool::json::is_member("member", value));
}

TEST(iscool_json_is_member, check_member_is_false)
{
  Json::Value value;
  value["member"] = 0;

  ASSERT_FALSE(iscool::json::is_member("not_member", value));
}

TEST(iscool_json_is_member, null_member_is_member)
{
  Json::Value value;
  value["member"] = Json::Value::null;

  ASSERT_TRUE(iscool::json::is_member("member", value));
}

TEST(iscool_json_is_member, check_is_member_does_not_add_member)
{
  Json::Value value;
  value["member"] = 0;

  iscool::json::is_member("not_member", value);
  ASSERT_FALSE(iscool::json::is_member("not_member", value));
}

TEST(iscool_json_is_member, check_is_member_on_non_object_is_false)
{
  Json::Value value(12);

  ASSERT_FALSE(iscool::json::is_member("not_member", value));
}
