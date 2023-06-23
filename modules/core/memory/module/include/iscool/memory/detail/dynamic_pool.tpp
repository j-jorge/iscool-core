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
#ifndef ISCOOL_MEMORY_DYNAMIC_POOL_TPP
#define ISCOOL_MEMORY_DYNAMIC_POOL_TPP

#include <iscool/contract/verify.hpp>

#include <algorithm>
#include <vector>

template <typename T, typename TypeTraits>
iscool::memory::dynamic_pool<T, TypeTraits>::dynamic_pool(std::size_t size)
  : _available(size)
  , _pool(size)
{
  for (std::size_t i(0); i != size; ++i)
    _available[i] = i;
}

template <typename T, typename TypeTraits>
iscool::memory::dynamic_pool<T, TypeTraits>::~dynamic_pool() = default;

template <typename T, typename TypeTraits>
typename iscool::memory::dynamic_pool<T, TypeTraits>::slot
iscool::memory::dynamic_pool<T, TypeTraits>::pick_available()
{
  std::size_t index;

  if (_available.empty())
    {
      index = _pool.size();
      _pool.emplace_back();
    }
  else
    {
      index = _available.back();
      _available.pop_back();
    }

  return { index, _pool[index] };
}

template <typename T, typename TypeTraits>
T& iscool::memory::dynamic_pool<T, TypeTraits>::get(std::size_t id)
{
  assert(id < _pool.size());
  assert(std::find(_available.begin(), _available.end(), id)
         == _available.end());

  return _pool[id];
}

template <typename T, typename TypeTraits>
void iscool::memory::dynamic_pool<T, TypeTraits>::release(std::size_t id)
{
  ic_verify(release_checked(id));
}

template <typename T, typename TypeTraits>
void iscool::memory::dynamic_pool<T, TypeTraits>::clear()
{
  const std::size_t pool_size(_pool.size());
  std::vector<bool> available(pool_size, false);

  for (std::size_t id : _available)
    available[id] = true;

  std::vector<std::size_t> remaining;
  std::size_t remaining_count(pool_size - _available.size());
  remaining.reserve(remaining_count);

  for (std::size_t i(0); i != pool_size; ++i)
    if (!available[i])
      remaining.push_back(i);

  assert(remaining.size() == remaining_count);

  while (remaining_count != 0)
    for (std::size_t i(0); i != remaining_count;)
      if (release_checked(remaining[i]))
        {
          --remaining_count;
          remaining[i] = remaining[remaining_count];
        }
      else
        ++i;
}

template <typename T, typename TypeTraits>
bool iscool::memory::dynamic_pool<T, TypeTraits>::release_checked(
    std::size_t id)
{
  assert(id < _pool.size());
  assert(std::find(_available.begin(), _available.end(), id)
         == _available.end());

  if (TypeTraits::clear(_pool[id]))
    {
      _available.push_back(id);
      return true;
    }

  return false;
}

#endif
