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
#ifndef ISCOOL_STYLE_DETAIL_PROPERTIES_H
#define ISCOOL_STYLE_DETAIL_PROPERTIES_H

#include "iscool/style/detail/declaration_ref.h"

#include <string>
#include <unordered_map>

namespace iscool
{
  namespace style
  {
    namespace detail
    {
      class properties
      {
      public:
        typedef std::unordered_map<std::string, float> numbers_map;
        typedef std::unordered_map<std::string, bool> booleans_map;

        typedef std::unordered_map<std::string, detail::declaration_ref>
            declaration_map;

        typedef std::unordered_map<std::string, std::string> string_map;

      public:
        properties();

      public:
        numbers_map numbers;
        booleans_map booleans;
        declaration_map declarations;
        string_map strings;
      };
    }
  }
}
#endif
