// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdint>
#include <string_view>

namespace iscool
{
  enum class iso_639_language_code : std::uint8_t;

  std::string_view to_string(iso_639_language_code c);
}
