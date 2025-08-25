// SPDX-License-Identifier: Apache-2.0
#include <iscool/iso_639_language_code.hpp>

#include <cassert>

std::string_view iscool::to_string(iso_639_language_code c)
{
  switch (c)
    {
    case iso_639_language_code::de:
      return "de";
    case iso_639_language_code::en:
      return "en";
    case iso_639_language_code::es:
      return "es";
    case iso_639_language_code::fi:
      return "fi";
    case iso_639_language_code::fr:
      return "fr";
    case iso_639_language_code::it:
      return "it";
    case iso_639_language_code::ja:
      return "ja";
    case iso_639_language_code::ko:
      return "ko";
    case iso_639_language_code::nl:
      return "nl";
    case iso_639_language_code::pl:
      return "pl";
    case iso_639_language_code::pt:
      return "pt";
    case iso_639_language_code::ru:
      return "ru";
    case iso_639_language_code::sv:
      return "sv";
    case iso_639_language_code::th:
      return "th";
    case iso_639_language_code::tr:
      return "tr";
    case iso_639_language_code::zh:
      return "zh";
    }

  assert(false);
  return "en";
}
