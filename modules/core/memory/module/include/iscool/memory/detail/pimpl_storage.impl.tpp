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
#ifndef ISCOOL_MEMORY_DETAIL_PIMPL_STORAGE_IMPL_TPP
#define ISCOOL_MEMORY_DETAIL_PIMPL_STORAGE_IMPL_TPP

#include <iscool/memory/detail/pimpl_storage.hpp>

#include <cassert>

namespace iscool
{
  namespace memory
  {
    namespace detail
    {
      template <std::size_t Needed, std::size_t Provided>
      struct assert_exact_space
      {
        static_assert(Needed == Provided,
                      "Incorrect capacity."
                      " See template instantiation for values.");
      };
    }
  }
}

template <typename T, std::size_t N>
template <typename... Args>
iscool::memory::detail::pimpl_storage<T, N>::pimpl_storage(Args&&... args)
{
  assert_exact_space<sizeof(T), N>();

  new (&_storage) T(std::forward<Args>(args)...);
}

template <typename T, std::size_t N>
iscool::memory::detail::pimpl_storage<T, N>::~pimpl_storage()
{
  get()->~T();
}

template <typename T, std::size_t N>
T* iscool::memory::detail::pimpl_storage<T, N>::get() const
{
  return reinterpret_cast<T*>(const_cast<decltype(_storage)*>(&_storage));
}

template <typename T>
template <typename... Args>
iscool::memory::detail::pimpl_storage<T, 0>::pimpl_storage(Args&&... args)
  : _pointer(new T(std::forward<Args>(args)...))
{}

template <typename T>
iscool::memory::detail::pimpl_storage<T, 0>::~pimpl_storage()
{}

template <typename T>
T* iscool::memory::detail::pimpl_storage<T, 0>::get() const
{
  return _pointer.get();
}

#endif
