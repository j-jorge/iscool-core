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
#ifndef ISCOOL_MEMORY_PIMPL_IMPL_TPP
#define ISCOOL_MEMORY_PIMPL_IMPL_TPP

#include <iscool/memory/detail/pimpl_storage.impl.tpp>
#include <iscool/memory/pimpl.hpp>

template <typename T, std::size_t N>
iscool::memory::pimpl<T, N>::pimpl() = default;

template <typename T, std::size_t N>
iscool::memory::pimpl<T, N>::pimpl(pimpl<T, N>&& that)
  : _storage(std::move(*that._storage.get()))
{}

template <typename T, std::size_t N>
iscool::memory::pimpl<T, N>::pimpl(const pimpl<T, N>& that)
  : _storage(*that._storage.get())
{}

template <typename T, std::size_t N>
template <typename... Args, typename OK>
iscool::memory::pimpl<T, N>::pimpl(Args&&... args)
  : _storage(std::forward<Args>(args)...)
{}

template <typename T, std::size_t N>
iscool::memory::pimpl<T, N>::~pimpl()
{}

template <typename T, std::size_t N>
iscool::memory::pimpl<T, N>&
iscool::memory::pimpl<T, N>::operator=(pimpl<T, N>&& that)
{
  *_storage.get() = std::move(*that._storage.get());
  return *this;
}

template <typename T, std::size_t N>
iscool::memory::pimpl<T, N>&
iscool::memory::pimpl<T, N>::operator=(const pimpl<T, N>& that)
{
  *_storage.get() = *that._storage.get();
  return *this;
}

template <typename T, std::size_t N>
T* iscool::memory::pimpl<T, N>::get() const
{
  return _storage.get();
}

template <typename T, std::size_t N>
T* iscool::memory::pimpl<T, N>::operator->() const
{
  return _storage.get();
}

template <typename T, std::size_t N>
T& iscool::memory::pimpl<T, N>::operator*() const
{
  return *_storage.get();
}

#endif
