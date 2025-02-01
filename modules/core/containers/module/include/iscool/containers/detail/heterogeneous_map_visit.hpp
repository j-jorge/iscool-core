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
      struct heterogeneous_map_visit;

      template <>
      struct heterogeneous_map_visit<0>
      {
        template <typename T, typename U>
        static void run(const T&, const U&);
      };

      template <std::size_t N>
      struct heterogeneous_map_visit
      {
        template <typename Key, typename Visitor, typename... T>
        static void run(const std::tuple<std::unordered_map<Key, T>...>& maps,
                        Visitor&& visitor);
      };
    }
  }
}

#include <iscool/containers/detail/heterogeneous_map_visit.tpp>
