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
#ifndef ISCOOL_COLLECTIONS_SORT_PERMUTATION_H
#define ISCOOL_COLLECTIONS_SORT_PERMUTATION_H

#include <vector>

namespace iscool
{
  namespace collections
  {
    template <typename Iterator>
    std::vector<std::size_t> sort_permutation(const Iterator& first,
                                              const Iterator& last);

    template <typename Iterator, typename Compare>
    std::vector<std::size_t> sort_permutation(const Iterator& first,
                                              const Iterator& last,
                                              const Compare& compare);
  }
}

#include "iscool/collections/detail/sort_permutation.tpp"

#endif
