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
#ifndef ISCOOL_META_DETAIL_TYPE_INDEX_H
#define ISCOOL_META_DETAIL_TYPE_INDEX_H

#include <iscool/meta/contains.hpp>

namespace iscool
{
  namespace meta
  {
    namespace detail
    {
      template <std::size_t I, typename T, typename... U>
      struct type_index;

      template <std::size_t I, typename T, typename... U>
      struct type_index_final : public std::integral_constant<std::size_t, I>
      {
        static_assert(
            !meta::contains<T, U...>::value,
            "Can't get the index of duplicated type in parameter pack.");
      };

      template <std::size_t I, typename T, typename Head, typename... Tail>
      struct type_index<I, T, Head, Tail...>
        : public std::conditional<std::is_same<T, Head>::value,
                                  type_index_final<I, T, Tail...>,
                                  type_index<I + 1, T, Tail...>>::type
      {};
    }
  }
}

#endif
