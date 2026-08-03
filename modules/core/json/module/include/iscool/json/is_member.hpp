// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <string_view>

namespace Json
{
  class Value;
}

namespace iscool::json
{
  bool is_member(std::string_view key, const Json::Value& json_value);
}
