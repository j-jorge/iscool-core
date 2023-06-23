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
#ifndef ISCOOL_MEMORY_PIMPL_H
#define ISCOOL_MEMORY_PIMPL_H

#include <iscool/memory/detail/pimpl_storage.hpp>

#include <tuple>
#include <type_traits>

namespace iscool
{
  namespace memory
  {
    template <typename T, std::size_t N = 0>
    class pimpl
    {
    public:
      pimpl();
      pimpl(pimpl<T, N>&& that);
      pimpl(const pimpl<T, N>&);

      template <
          typename... Args,
          typename OK = typename std::enable_if<!std::is_same<
              std::tuple<pimpl<T, N>>,
              std::tuple<typename std::decay<Args>::type...>>::value>::type>
      pimpl(Args&&... args);

      ~pimpl();

      pimpl<T, N>& operator=(pimpl<T, N>&& that);
      pimpl<T, N>& operator=(const pimpl<T, N>&);

      T* get() const;

      T* operator->() const;
      T& operator*() const;

    private:
      detail::pimpl_storage<T, N> _storage;
    };
  }
}

#endif
