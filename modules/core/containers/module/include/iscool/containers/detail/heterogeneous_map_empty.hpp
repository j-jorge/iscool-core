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
#pragma once

namespace iscool
{
  namespace containers
  {
    namespace detail
    {
      template <std::size_t N>
      struct heterogeneous_map_empty;

      template <>
      struct heterogeneous_map_empty<0>
      {
        template <typename T>
        static bool run(const T&);
      };

      template <std::size_t N>
      struct heterogeneous_map_empty
      {
        template <typename Key, typename... T>
        static bool run(const std::tuple<std::unordered_map<Key, T>...>& maps);
      };
    }
  }
}

#include <iscool/containers/detail/heterogeneous_map_empty.tpp>
