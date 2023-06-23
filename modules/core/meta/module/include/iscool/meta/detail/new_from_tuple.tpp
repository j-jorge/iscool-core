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
#ifndef ISCOOL_META_NEW_FROM_TUPLE_TPP
#define ISCOOL_META_NEW_FROM_TUPLE_TPP

#include "iscool/meta/make_indices.h"

#include <tuple>

namespace iscool
{
  namespace meta
  {
    namespace detail
    {
      template <typename T, typename Tuple, typename Indices>
      struct new_from_tuple_helper;

      template <typename T, typename Tuple, std::size_t... I>
      struct new_from_tuple_helper<T, Tuple, indices<I...>>
      {
        static T* call(Tuple&& tuple);
      };
    }
  }
}

template <typename T, typename Tuple>
T* iscool::meta::new_from_tuple(Tuple&& tuple)
{
  return detail::new_from_tuple_helper<
      T, Tuple,
      typename make_indices<std::tuple_size<typename std::decay<
          Tuple>::type>::value>::type>::call(std::forward<Tuple>(tuple));
}

template <typename T, typename Tuple, std::size_t... I>
T* iscool::meta::detail::new_from_tuple_helper<
    T, Tuple, iscool::meta::indices<I...>>::call(Tuple&& args)
{
  return new T(std::forward<typename std::tuple_element<
                   I, typename std::decay<Tuple>::type>::type>(
      std::get<I>(std::forward<Tuple>(args)))...);
}

#endif
