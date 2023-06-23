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
#include <iscool/i18n/numeric_punctuation.hpp>

iscool::i18n::numeric_punctuation::numeric_punctuation(
    char decimal_point, char thousands_separator, std::string grouping)
  : _decimal_point(decimal_point)
  , _thousands_separator(thousands_separator)
  , _grouping(std::move(grouping))
{}

char iscool::i18n::numeric_punctuation::do_decimal_point() const
{
  return _decimal_point;
}

char iscool::i18n::numeric_punctuation::do_thousands_sep() const
{
  return _thousands_separator;
}

std::string iscool::i18n::numeric_punctuation::do_grouping() const
{
  return _grouping;
}
