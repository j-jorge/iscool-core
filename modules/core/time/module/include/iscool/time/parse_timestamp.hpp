// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <chrono>
#include <string_view>

namespace iscool::time
{
  bool parse_timestamp(std::chrono::system_clock::time_point& t,
                       std::string_view s);
}
