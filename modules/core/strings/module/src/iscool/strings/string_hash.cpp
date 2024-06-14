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
#include <iscool/strings/string_hash.hpp>

#include <iscool/strings/dynamic_hash.hpp>

#ifdef ISCOOL_ENABLE_DEBUG_STRING_HASH
  #include <cassert>
  #include <unordered_map>
#endif

iscool::strings::string_hash::string_hash(const std::string& s)
  : _hash(dynamic_hash(s.c_str())) DEBUG_STRING_HASH_FIELD(_string(s))
        DEBUG_STRING_HASH_FIELD(_checked(false))
{
  DEBUG_STRING_HASH(check_duplicate());
}

bool iscool::strings::string_hash::operator<(const string_hash& that) const
{
  return _hash < that._hash;
}

bool iscool::strings::string_hash::operator==(const string_hash& that) const
{
  return _hash == that._hash;
}

bool iscool::strings::string_hash::operator!=(const string_hash& that) const
{
  return _hash != that._hash;
}

iscool::strings::hash_type iscool::strings::string_hash::get_hash_code() const
{
  DEBUG_STRING_HASH(check_duplicate());
  return _hash;
}

#ifdef ISCOOL_ENABLE_DEBUG_STRING_HASH
void iscool::strings::string_hash::check_duplicate() const
{
  if (_checked)
    return;

  _checked = true;

  static std::unordered_map<std::size_t, std::string> strings;

  const auto it(strings.find(_hash));
  (void)it;
  assert((it == strings.end()) || (it->second == _string));
  strings[_hash] = _string;
}
#endif

std::size_t std::hash<iscool::strings::string_hash>::operator()(
    const iscool::strings::string_hash& h) const
{
  return h.get_hash_code();
}
