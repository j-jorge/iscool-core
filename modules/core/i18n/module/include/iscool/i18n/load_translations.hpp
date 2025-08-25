// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/language_name.hpp>

#include <iosfwd>

namespace iscool
{
  namespace i18n
  {
    bool load_translations(iscool::language_name language_code,
                           std::istream& stream);
  }
}
