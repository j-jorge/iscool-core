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
#ifndef ISCOOL_JNI_DETAIL_NATIVE_CALL_MANAGER_TPP
#define ISCOOL_JNI_DETAIL_NATIVE_CALL_MANAGER_TPP

#include <iscool/jni/detail/variadic_native_callback.hpp>

template <typename... Args>
jlong iscool::jni::detail::native_call_manager::register_callback(
    native_callback_lifespan lifespan,
    const std::function<void(Args...)>& callback)
{
  auto* const pointer(
      new variadic_native_callback<Args...>(lifespan, callback));
  _callbacks.push_back(pointer);

  return reinterpret_cast<jlong>(pointer);
}

#endif
