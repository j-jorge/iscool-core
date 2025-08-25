// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/i18n/detail/default_language_name.hpp>
#include <iscool/i18n/detail/get_locale_for_numeric_display.hpp>
#include <iscool/i18n/detail/num_put_disambiguation.hpp>

#include <sstream>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type
iscool::i18n::numeric::to_string(const T& value)
{
  std::ostringstream formatter;

  formatter.imbue(detail::get_locale_for_numeric_display(
      formatter.getloc(), iscool::i18n::detail::default_language_name));

  const std::num_put<char>& facet(
      std::use_facet<std::num_put<char>>(formatter.getloc()));

  facet.put(
      std::ostreambuf_iterator<char>(formatter), formatter, ' ',
      static_cast<typename detail::num_put_disambiguation<T>::type>(value));

  return formatter.str();
}
