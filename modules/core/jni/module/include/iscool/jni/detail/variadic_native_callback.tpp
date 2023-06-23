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
#ifndef ISCOOL_JNI_DETAIL_VARIADIC_NATIVE_CALLBACK_TPP
#define ISCOOL_JNI_DETAIL_VARIADIC_NATIVE_CALLBACK_TPP

#include "iscool/jni/bad_cast.h"
#include "iscool/jni/detail/call_native_function.h"
#include "iscool/jni/log_context.h"
#include "iscool/jni/throw_java_exception.h"

#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/error.h"

template <typename... Args>
iscool::jni::detail::variadic_native_callback<
    Args...>::variadic_native_callback(native_callback_lifespan lifespan,
                                       const callback_type& callback)
  : native_callback(lifespan)
  , _callback(callback)
{}

template <typename... Args>
void iscool::jni::detail::variadic_native_callback<Args...>::operator()(
    const java_ptr<jobjectArray>& arguments)
{
  try
    {
      call_native_function(_callback, arguments);
    }
  catch (const iscool::jni::bad_cast& exception)
    {
      ic_causeless_log(iscool::log::nature::error(), log_context(),
                       "Invalid cast: %s", exception.what());
      throw_java_exception(exception.what());
    }
}

#endif
