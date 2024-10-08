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
#ifndef ISCOOL_META_COMBINE_OR_H
#define ISCOOL_META_COMBINE_OR_H

namespace iscool
{
  namespace meta
  {
    template <bool... Value>
    struct combine_or;

    template <bool Value>
    struct combine_or<Value>
    {
      enum
      {
        value = Value
      };
    };

    template <bool V1, bool... Values>
    struct combine_or<V1, Values...>
    {
      enum
      {
        value = V1 || combine_or<Values...>::value
      };
    };
  }
}

#include <iscool/meta/detail/combine_or.tests.hpp>

#endif
