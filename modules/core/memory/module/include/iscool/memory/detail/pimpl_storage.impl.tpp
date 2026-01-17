// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/memory/detail/pimpl_storage.hpp>

#include <cassert>

namespace iscool::memory::detail
{
  template <std::size_t Needed, std::size_t Provided>
  struct assert_exact_space
  {
    static_assert(Needed == Provided,
                  "Incorrect capacity."
                  " See template instantiation for values.");
  };

  template <std::size_t Needed, std::size_t Provided>
  struct assert_valid_alignment
  {
    static_assert(Provided % Needed == 0);
  };
}

template <typename T, std::size_t N>
template <typename... Args>
iscool::memory::detail::pimpl_storage<T, N>::pimpl_storage(Args&&... args)
{
  assert_exact_space<sizeof(T), N>();
  assert_valid_alignment<alignof(T), alignof(_storage)>();

  new (_storage) T(std::forward<Args>(args)...);
}

template <typename T, std::size_t N>
iscool::memory::detail::pimpl_storage<T, N>::pimpl_storage::~pimpl_storage()
{
  get()->~T();
}

template <typename T, std::size_t N>
T* iscool::memory::detail::pimpl_storage<T, N>::get() const
{
  return reinterpret_cast<T*>(const_cast<std::byte*>(_storage));
}

template <typename T>
template <typename... Args>
iscool::memory::detail::pimpl_storage<T, 0>::pimpl_storage(Args&&... args)
  : _pointer(new T(std::forward<Args>(args)...))
{}

template <typename T>
iscool::memory::detail::pimpl_storage<T, 0>::pimpl_storage::~pimpl_storage()
{}

template <typename T>
T* iscool::memory::detail::pimpl_storage<T, 0>::get() const
{
  return _pointer.get();
}
