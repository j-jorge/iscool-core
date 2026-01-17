// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>

namespace iscool::memory::detail
{
  template <typename T, std::size_t N>
  class pimpl_storage
  {
  public:
    template <typename... Args>
    pimpl_storage(Args&&... args);

    pimpl_storage(pimpl_storage<T, N>&&) = delete;
    pimpl_storage(const pimpl_storage<T, N>&) = delete;

    ~pimpl_storage();

    pimpl_storage<T, N>& operator=(pimpl_storage<T, N>&&) = delete;

    pimpl_storage<T, N>& operator=(const pimpl_storage<T, N>&) = delete;

    T* get() const;

  private:
    alignas(std::max_align_t) std::byte _storage[N];
  };

  template <typename T>
  class pimpl_storage<T, 0>
  {
  public:
    template <typename... Args>
    pimpl_storage(Args&&... args);

    pimpl_storage(pimpl_storage<T, 0>&&) = delete;
    pimpl_storage(const pimpl_storage<T, 0>&) = delete;

    ~pimpl_storage();

    pimpl_storage<T, 0>& operator=(pimpl_storage<T, 0>&&) = delete;

    pimpl_storage<T, 0>& operator=(const pimpl_storage<T, 0>&) = delete;

    T* get() const;

  private:
    std::unique_ptr<T> _pointer;
  };
}
