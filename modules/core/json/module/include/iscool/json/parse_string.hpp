// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <json/value.h>

#include <string_view>

namespace iscool::json
{
  Json::Value parse_string(std::string_view string);
}
