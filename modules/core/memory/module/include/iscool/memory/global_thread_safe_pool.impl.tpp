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
#ifndef ISCOOL_MEMORY_GLOBAL_THREAD_SAFE_POOL_IMPL_TPP
#define ISCOOL_MEMORY_GLOBAL_THREAD_SAFE_POOL_IMPL_TPP

#include <iscool/memory/global_thread_safe_pool.hpp>
#include <iscool/memory/pool.impl.tpp>

template <typename T>
iscool::memory::thread_safe_pool<T>&
iscool::memory::get_global_thread_safe_pool()
{
  static thread_safe_pool<T> result;
  return result;
}

#endif
