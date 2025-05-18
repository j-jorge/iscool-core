// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/json/detail/cast_fwd.hpp>

#include <cstdint>

namespace Json
{
  class Value;
}

namespace iscool::json::detail
{
  template <>
  struct cast<std::int16_t>
  {
    static bool is_valid(const Json::Value& value);
    static std::int16_t value(const Json::Value& value);
  };
}
