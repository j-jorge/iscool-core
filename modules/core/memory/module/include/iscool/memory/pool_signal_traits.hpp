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
#ifndef ISCOOL_MEMORY_POOL_SIGNAL_TRAITS_H
#define ISCOOL_MEMORY_POOL_SIGNAL_TRAITS_H

namespace iscool
{
  namespace memory
  {
    template <typename S>
    struct pool_signal_traits
    {
      static bool clear(S& value);
    };
  }
}

#include <iscool/memory/detail/pool_signal_traits.tpp>

#endif
