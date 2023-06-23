/*
  Copyright 2018-present IsCool Entertainment

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#include <iscool/i18n/detail/get_locale_for_numeric_display.hpp>

#include <iscool/i18n/numeric_punctuation.hpp>

#include <iscool/optional.hpp>
#include <iscool/optional.impl.tpp>

namespace iscool
{
  namespace i18n
  {
    namespace numeric
    {
      namespace detail
      {
        static numeric_punctuation*
        allocate_numeric_punctuation(const std::string& language_code);
      }
    }
  }
}

const std::locale&
iscool::i18n::numeric::detail::get_locale_for_numeric_display(
    const std::locale& from, const std::string& language_code)
{
  static iscool::optional<std::locale> cached_locale;
  static std::string cached_language_code;

  if (!cached_locale || (cached_language_code != language_code))
    {
      cached_locale.emplace(from, allocate_numeric_punctuation(language_code));
      cached_language_code = language_code;
    }

  return *cached_locale;
}

iscool::i18n::numeric_punctuation*
iscool::i18n::numeric::detail::allocate_numeric_punctuation(
    const std::string& language_code)
{
  char thousands_separator;
  char decimal_point;

  if (language_code == "fr")
    {
      thousands_separator = ' ';
      decimal_point = ',';
    }
  else if ((language_code == "it") || (language_code == "de")
           || (language_code == "es") || (language_code == "nl"))
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
