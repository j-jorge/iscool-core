// SPDX-License-Identifier: Apache-2.0
#include <iscool/i18n/detail/assign_plural_index.hpp>

#include <iscool/i18n/detail/plural_index.hpp>

#include <iscool/iso_639_language_code.hpp>
#include <iscool/language_name.hpp>

#include <cassert>

#define assign_index_expression_and_return(expression)                        \
  {                                                                           \
    plural_index = [](std::uint64_t n) -> std::uint8_t                        \
    {                                                                         \
      return expression;                                                      \
    };                                                                        \
                                                                              \
    return;                                                                   \
  }

void iscool::i18n::detail::assign_plural_index(
    iscool::language_name language_name)
{
  /*
    See the table on this page for updates:
    http://localization-guide.readthedocs.org/en/latest/l10n/pluralforms.html
  */

  switch (language_name)
    {
    case iscool::language_name::pt_BR:
      assign_index_expression_and_return((n > 1) ? 1 : 0);
    default:
      break;
    }

  const iscool::iso_639_language_code language_code =
      iscool::to_language_code(language_name);

  switch (language_code)
    {
    case iscool::iso_639_language_code::br:
    case iscool::iso_639_language_code::fr:
    case iscool::iso_639_language_code::kab:
    case iscool::iso_639_language_code::oc:
    case iscool::iso_639_language_code::tr:
      assign_index_expression_and_return((n > 1) ? 1 : 0);

    case iscool::iso_639_language_code::de:
    case iscool::iso_639_language_code::en:
    case iscool::iso_639_language_code::es:
    case iscool::iso_639_language_code::fi:
    case iscool::iso_639_language_code::it:
    case iscool::iso_639_language_code::nl:
    case iscool::iso_639_language_code::pt:
    case iscool::iso_639_language_code::sv:
      assign_index_expression_and_return((n != 1) ? 1 : 0);

    case iscool::iso_639_language_code::ja:
    case iscool::iso_639_language_code::ko:
    case iscool::iso_639_language_code::th:
    case iscool::iso_639_language_code::zh:
      assign_index_expression_and_return(0);

    case iscool::iso_639_language_code::pl:
      assign_index_expression_and_return(
          (n == 1) ? 0
                   : ((n % 10 >= 2) && (n % 10 <= 4)
                              && ((n % 100 < 10) || (n % 100 >= 20))
                          ? 1
                          : 2));

    case iscool::iso_639_language_code::ru:
    case iscool::iso_639_language_code::uk:
      assign_index_expression_and_return(
          ((n % 10 == 1) && (n % 100 != 11))
              ? 0
              : ((n % 10 >= 2) && (n % 10 <= 4)
                         && ((n % 100 < 10) || (n % 100 >= 20))
                     ? 1
                     : 2));
    }

  assert(false);
}

#undef assign_index_expression_and_return
