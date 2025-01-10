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

#include <deque>
#include <vector>

namespace iscool::memory
{
  template <typename T, typename TypeTraits>
  class dynamic_pool
  {
  public:
    struct slot
    {
      std::size_t id;
      T* value;
    };

  public:
    explicit dynamic_pool(std::size_t size);
    ~dynamic_pool();

    slot pick_available();
    T& get(std::size_t id);
    void release(std::size_t id);

    void clear();

  private:
    bool release_checked(std::size_t id);

  private:
    std::vector<std::size_t> _available;
    std::deque<T> _pool;
  };
}

#include <iscool/memory/detail/dynamic_pool.tpp>
