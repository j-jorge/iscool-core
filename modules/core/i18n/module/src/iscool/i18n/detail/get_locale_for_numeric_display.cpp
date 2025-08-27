// SPDX-License-Identifier: Apache-2.0
#include <iscool/i18n/detail/get_locale_for_numeric_display.hpp>

#include <iscool/i18n/numeric_punctuation.hpp>

#include <iscool/iso_639_language_code.hpp>
#include <iscool/language_name.hpp>
#include <iscool/optional.hpp>
#include <iscool/optional.impl.tpp>

namespace iscool::i18n::numeric::detail
{
  static numeric_punctuation*
  allocate_numeric_punctuation(iscool::language_name language_name);
}

const std::locale&
iscool::i18n::numeric::detail::get_locale_for_numeric_display(
    const std::locale& from, iscool::language_name language_name)
{
  static iscool::optional<std::locale> cached_locale;
  static iscool::language_name cached_language_name;

  if (!cached_locale || (cached_language_name != language_name))
    {
      cached_locale.emplace(from, allocate_numeric_punctuation(language_name));
      cached_language_name = language_name;
    }

  return *cached_locale;
}

iscool::i18n::numeric_punctuation*
iscool::i18n::numeric::detail::allocate_numeric_punctuation(
    iscool::language_name language_name)
{
  char thousands_separator;
  char decimal_point;

  const iscool::iso_639_language_code language_code =
      iscool::to_language_code(language_name);

  if ((language_code == iscool::iso_639_language_code::br)
      || (language_code == iscool::iso_639_language_code::fr))
    {
      thousands_separator = ' ';
      decimal_point = ',';
    }
  else if ((language_code == iscool::iso_639_language_code::it)
           || (language_code == iscool::iso_639_language_code::de)
           || (language_code == iscool::iso_639_language_code::es)
           || (language_code == iscool::iso_639_language_code::nl))
    {
      thousands_separator = '.';
      decimal_point = ',';
    }
  else
    {
      thousands_separator = ',';
      decimal_point = '.';
    }

  // The first character in the grouping is the number of digits in the
  // rightmost group
  return new numeric_punctuation(decimal_point, thousands_separator, "\3");
}
