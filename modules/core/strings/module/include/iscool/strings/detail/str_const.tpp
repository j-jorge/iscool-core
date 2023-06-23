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
#ifndef ISCOOL_STRINGS_STR_CONST_TPP
#define ISCOOL_STRINGS_STR_CONST_TPP

#include "iscool/strings/detail/hash_parameters.h"

template <std::size_t N>
constexpr iscool::strings::str_const::str_const(const char (&s)[N])
  : _begin(s)
  , _size(N - 1)
{
  static_assert(N >= 1, "not a string literal");
}

constexpr iscool::strings::str_const::operator const char*() const
{
  return _begin;
}

constexpr std::size_t iscool::strings::str_const::size() const
{
  return _size;
}

constexpr iscool::strings::hash_type iscool::strings::str_const::hash() const
{
  return hash(_size);
}

constexpr iscool::strings::hash_type
iscool::strings::str_const::hash(std::size_t pos) const
{
  return (pos == 0) ? detail::hash_seed
                    : hash(pos - 1) * detail::hash_factor + _begin[pos - 1];
}

static_assert(iscool::strings::str_const("abc").size() == 3,
              "str_const size is incorrect");
static_assert(iscool::strings::str_const("a").hash() == 4031397658,
              "str_const hash is incorrect");

#endif
