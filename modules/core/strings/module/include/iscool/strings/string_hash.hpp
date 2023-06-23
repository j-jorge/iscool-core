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
#ifndef ISCOOL_STRINGS_STRING_HASH_H
#define ISCOOL_STRINGS_STRING_HASH_H

#include <iscool/strings/hash_type.hpp>

#include <string>

#ifndef ISCOOL_ENABLE_DEBUG_STRING_HASH
  #ifndef NDEBUG
    #define ISCOOL_ENABLE_DEBUG_STRING_HASH
  #endif
#endif

#ifdef ISCOOL_ENABLE_DEBUG_STRING_HASH
  #define DEBUG_STRING_HASH(e) e
  #define DEBUG_STRING_HASH_FIELD(e) , e
#else
  #define DEBUG_STRING_HASH(e)
  #define DEBUG_STRING_HASH_FIELD(e)
#endif

namespace iscool
{
  namespace strings
  {
    class string_hash
    {
    public:
      string_hash(const std::string& s);

      template <std::size_t N>
      constexpr string_hash(const char (&s)[N]);

      bool operator<(const string_hash& that) const;
      bool operator==(const string_hash& that) const;
      bool operator!=(const string_hash& that) const;

      hash_type get_hash_code() const;

    private:
#ifdef ISCOOL_ENABLE_DEBUG_STRING_HASH
      void check_duplicate() const;
#endif

    private:
      const hash_type _hash;
      DEBUG_STRING_HASH(const std::string _string;)
      DEBUG_STRING_HASH(mutable bool _checked;)
    };
  }
}

namespace std
{
  template <>
  struct hash<iscool::strings::string_hash>
  {
    size_t operator()(const iscool::strings::string_hash& h) const;
  };
}

#include <iscool/strings/detail/string_hash.tpp>

#endif
