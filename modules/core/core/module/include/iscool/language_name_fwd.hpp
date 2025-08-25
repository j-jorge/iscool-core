// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/iso_639_language_code_fwd.hpp>

#include <cstdint>
#include <string_view>

namespace iscool
{
  enum class language_name : std::uint8_t;

  iso_639_language_code to_language_code(language_name c);

  std::string_view to_string(language_name c);
  language_name from_string_with_fallback(std::string_view s);

  std::string_view to_human_string(language_name c);
}
