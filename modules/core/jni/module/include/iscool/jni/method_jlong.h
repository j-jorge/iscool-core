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
#ifndef ISCOOL_JNI_METHOD_JLONG_H
#define ISCOOL_JNI_METHOD_JLONG_H

#include "iscool/jni/detail/method_base.h"
#include "iscool/jni/java_ptr.h"
#include "iscool/jni/method.h"

namespace iscool
{
  namespace jni
  {
    template <>
    class method<jlong> : public detail::method_base
    {
    public:
      using detail::method_base::method_base;

      template <typename... Arg>
      jlong operator()(const java_ptr<jobject>& self, Arg&&... args) const;
    };
  }
}

#include "iscool/jni/detail/method_jlong.tpp"

#endif
