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
#ifndef ISCOOL_COLLECTIONS_APPEND_H
#define ISCOOL_COLLECTIONS_APPEND_H

#include <memory>

namespace iscool
{
  namespace collections
  {
    template <template <typename, typename> class OutputContainer, typename T,
              template <typename, typename> class InputContainer, typename U>
    void append(OutputContainer<T, std::allocator<T>>& output,
                const InputContainer<U, std::allocator<U>>& input);
  }
}

#include <iscool/collections/detail/append.tpp>

#endif
