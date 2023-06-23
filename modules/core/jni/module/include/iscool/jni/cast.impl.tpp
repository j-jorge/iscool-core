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
#ifndef ISCOOL_JNI_CAST_IMPL_TPP
#define ISCOOL_JNI_CAST_IMPL_TPP

#include "iscool/jni/cast.h"
#include "iscool/jni/detail/cast_fwd.h"

template <typename T>
T iscool::jni::cast(jobject value)
{
  return detail::cast<T>::value(value);
}

#endif
