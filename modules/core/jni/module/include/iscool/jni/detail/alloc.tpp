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
#ifndef ISCOOL_JNI_DETAIL_ALLOC_H
#define ISCOOL_JNI_DETAIL_ALLOC_H

#include <iscool/jni/detail/get_method_argument.hpp>
#include <iscool/jni/detail/get_method_info.hpp>

template <typename... Arg>
iscool::jni::java_ptr<jobject> iscool::jni::alloc(const char* class_name,
                                                  const char* signature,
                                                  Arg&&... args)
{
  const detail::method_info m(
      detail::get_method_info(class_name, "<init>", signature));

  const jobject result(m.env->NewObject(
      m.class_id.get(), m.method_id,
      detail::get_method_argument<Arg>::get(std::forward<Arg>(args))...));

  return java_ptr<jobject>(result);
}

#endif
