// SPDX-License-Identifier: Apache-2.0
#include <iscool/i18n/load_translations.hpp>

#include <iscool/i18n/detail/assign_plural_index.hpp>
#include <iscool/i18n/detail/default_language_name.hpp>

#include "moFileReader/moFileReader.h"

bool iscool::i18n::load_translations(iscool::language_name language_name,
                                     std::istream& stream)
{
  const std::string data(std::istreambuf_iterator<char>(stream), {});
  moFileLib::moFileReader& reader(
      moFileLib::moFileReaderSingleton::GetInstance());
  reader.ClearTable();
  const moFileLib::moFileReader::eErrorCode error(reader.ParseData(data));

  detail::assign_plural_index(language_name);
  detail::default_language_name = language_name;

  if (error == moFileLib::moFileReader::EC_SUCCESS)
    return true;

  return false;
}
