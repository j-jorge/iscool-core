// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/json/detail/cast_fwd.hpp>

#include <cstdint>

namespace Json
{
  class Value;
}

namespace iscool
{
  namespace json
  {
    namespace detail
    {
      template <>
      struct cast<std::uint16_t>
      {
        static bool is_valid(const Json::Value& value);
        static std::uint16_t value(const Json::Value& value);
      };
    }
  }
}
