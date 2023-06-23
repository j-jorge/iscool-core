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
#ifndef ISCOOL_JNI_STATIC_METHOD_JBOOLEAN_TPP
#define ISCOOL_JNI_STATIC_METHOD_JBOOLEAN_TPP

#include "iscool/jni/check_java_exception.h"
#include "iscool/jni/detail/get_method_argument.h"

template <typename... Arg>
jboolean iscool::jni::static_method<jboolean>::operator()(Arg&&... args) const
{
  assert(check_java_exception());

  const jboolean result(_env->CallStaticBooleanMethod(
      _class.get(), _method,
      detail::get_method_argument<Arg>::get(std::forward<Arg>(args))...));

  assert(check_java_exception());

  return result;
}

#endif
