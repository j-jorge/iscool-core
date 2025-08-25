// SPDX-License-Identifier: Apache-2.0
#include <iscool/system/language_name.hpp>

#include <iscool/language_name.hpp>

#include <cstdlib>
#include <cstring>

iscool::language_name iscool::system::get_language_name()
{
  const char* const lang = std::getenv("LANG");

  if (lang == nullptr)
    return iscool::language_name::en_GB;

  const char* const dot = std::strchr(lang, '.');

  if (dot == nullptr)
    return iscool::from_string_with_fallback(lang);

  return iscool::from_string_with_fallback(std::string_view(lang, dot - lang));
}
