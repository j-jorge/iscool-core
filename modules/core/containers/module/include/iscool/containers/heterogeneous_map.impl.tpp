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
#ifndef ISCOOL_CONTAINERS_HETEROGENEOUS_MAP_TPP
#define ISCOOL_CONTAINERS_HETEROGENEOUS_MAP_TPP

#include "iscool/containers/detail/heterogeneous_map_clear.h"
#include "iscool/containers/detail/heterogeneous_map_empty.h"
#include "iscool/containers/detail/heterogeneous_map_visit.h"
#include "iscool/meta/type_index.h"
#include "iscool/none.h"

template <typename Key, typename... T>
template <typename U>
void iscool::containers::heterogeneous_map<Key, T...>::set(const Key& key,
                                                           const U& value)
{
  std::get<meta::type_index<U, T...>::value>(_maps)[key] = value;
}

template <typename Key, typename... T>
template <typename U>
bool iscool::containers::heterogeneous_map<Key, T...>::has(
    const Key& key) const
{
  const auto& map(std::get<meta::type_index<U, T...>::value>(_maps));

  return map.find(key) != map.end();
}

template <typename Key, typename... T>
template <typename U>
iscool::optional<U>
iscool::containers::heterogeneous_map<Key, T...>::get(const Key& key) const
{
  const auto& map(std::get<meta::type_index<U, T...>::value>(_maps));
  const auto it(map.find(key));

  if (it != map.end())
    return it->second;

  return iscool::none;
}

template <typename Key, typename... T>
template <typename U>
void iscool::containers::heterogeneous_map<Key, T...>::erase(const Key& key)
{
  auto& map(std::get<meta::type_index<U, T...>::value>(_maps));

  map.erase(key);
}

template <typename Key, typename... T>
template <typename Visitor>
void iscool::containers::heterogeneous_map<Key, T...>::visit(
    Visitor&& visitor) const
{
  detail::heterogeneous_map_visit<sizeof...(T)>::run(
      _maps, std::forward<Visitor>(visitor));
}

template <typename Key, typename... T>
bool iscool::containers::heterogeneous_map<Key, T...>::empty() const
{
  return detail::heterogeneous_map_empty<sizeof...(T)>::run(_maps);
}

template <typename Key, typename... T>
void iscool::containers::heterogeneous_map<Key, T...>::swap(
    heterogeneous_map<Key, T...>& that)
{
  _maps.swap(that._maps);
}

template <typename Key, typename... T>
void iscool::containers::heterogeneous_map<Key, T...>::clear()
{
  detail::heterogeneous_map_clear<sizeof...(T)>::run(_maps);
}

#endif
