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
#ifndef META_CONTAINS_H
#define META_CONTAINS_H

#include <type_traits>

namespace iscool
{
    namespace meta
    {
        template< typename T, typename... U >
        struct contains;

        template< typename T, typename Head, typename... Tail >
        struct contains< T, Head, Tail... >
            : public std::conditional
              <
                  std::is_same< T, Head >::value,
                  std::true_type,
                  contains<T, Tail...>
              >::type
        {};

        template<typename T>
        struct contains<T>:
            public std::false_type
        {};
    }
}

#endif
