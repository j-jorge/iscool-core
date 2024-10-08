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
#ifndef ISCOOL_JNI_DETAIL_METHOD_JOBJECT_HELPER_H
#define ISCOOL_JNI_DETAIL_METHOD_JOBJECT_HELPER_H

#include <iscool/jni/detail/method_base.hpp>
#include <iscool/jni/java_ptr.hpp>

namespace iscool
{
  namespace jni
  {
    namespace detail
    {
      template <typename T>
      class method_jobject_helper : public method_base
      {
      public:
        using detail::method_base::method_base;

        template <typename... Arg>
        T operator()(const java_ptr<jobject>& self, Arg&&... args) const;
      };
    }
  }
}

#include <iscool/jni/detail/method_jobject_helper.tpp>

#endif
