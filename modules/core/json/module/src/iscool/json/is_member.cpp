// SPDX-License-Identifier: Apache-2.0
#include <iscool/json/is_member.hpp>

#include <json/value.h>

bool iscool::json::is_member(std::string_view key,
                             const Json::Value& json_value)
{
  if (json_value.type() != Json::objectValue)
    return false;

  return json_value.find(key.begin(), key.end()) != nullptr;
}
