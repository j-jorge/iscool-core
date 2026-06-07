// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <string>

namespace Json
{
  class Value;
}

namespace iscool::json
{
  bool write_to_string(std::string& output, const Json::Value& value);
}
