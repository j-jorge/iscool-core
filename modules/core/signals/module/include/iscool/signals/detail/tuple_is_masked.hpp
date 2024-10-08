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
#ifndef ISCOOL_SIGNALS_DETAIL_TUPLE_IS_MASKED_H
#define ISCOOL_SIGNALS_DETAIL_TUPLE_IS_MASKED_H

#include <iscool/signals/detail/any_tuple_has_type_at_index.hpp>

#include <iscool/meta/combine_and.hpp>
#include <iscool/meta/indices.hpp>

namespace iscool
{
  namespace signals
  {
    namespace detail
    {
      template <typename Indices, typename Tuple, typename... Mask>
      struct tuple_is_masked;

      template <std::size_t... IndexInTuple, typename Tuple, typename... Mask>
      struct tuple_is_masked<iscool::meta::indices<IndexInTuple...>, Tuple,
                             Mask...>
      {
        enum
        {
          value = iscool::meta::combine_and < any_tuple_has_type_at_index
                  < IndexInTuple,
          Tuple,
          Mask... > ::value... > ::value
        };
      };

      template <std::size_t... IndexInTuple, typename Tuple>
      struct tuple_is_masked<iscool::meta::indices<IndexInTuple...>, Tuple>
      {
        enum
        {
          value = false
        };
      };
    }
  }
}

#include <iscool/signals/detail/tuple_is_masked.tests.hpp>

#endif
