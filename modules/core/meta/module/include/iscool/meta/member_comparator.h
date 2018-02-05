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
#ifndef ISCOOL_META_MEMBER_COMPARATOR_H
#define ISCOOL_META_MEMBER_COMPARATOR_H

#include <type_traits>

#define member_comparator( T, Member, Operator )                        \
    []( T const& a, T const& b ) -> bool                                \
    {                                                                   \
        static_assert                                                   \
            ( std::is_same                                              \
              <                                                         \
                  bool,                                                 \
                  decltype( a Member Operator b Member )                \
              >::value,                                                 \
              "member_comparator() needs a boolean operator." );        \
                                                                        \
        return a Member Operator b Member;                              \
}

#endif
