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
#ifndef ISCOOL_META_TYPE_INDEX_H
#define ISCOOL_META_TYPE_INDEX_H

#include <iscool/meta/detail/type_index.hpp>

namespace iscool
{
  namespace meta
  {
    template <typename T, typename... U>
    struct type_index
    {
      static constexpr std::size_t value =
          detail::type_index<0, T, U...>::value;
    };
  }
}

#endif
