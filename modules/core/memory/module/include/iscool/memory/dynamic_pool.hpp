// SPDX-License-Identifier: Apache-2.0
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
