// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <string_view>

namespace iscool::http::json::headers
{
  constexpr std::string_view accept("Accept: application/json");
  constexpr std::string_view
      content_type("Content-Type: application/json; charset=utf-8");
}
