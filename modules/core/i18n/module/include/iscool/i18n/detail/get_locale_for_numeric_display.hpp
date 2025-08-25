// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/language_name_fwd.hpp>

#include <locale>

namespace iscool::i18n::numeric::detail
{
  const std::locale&
  get_locale_for_numeric_display(const std::locale& from,
                                 iscool::language_name language_name);
}
