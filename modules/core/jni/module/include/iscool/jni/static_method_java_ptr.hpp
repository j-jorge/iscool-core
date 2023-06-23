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
#ifndef ISCOOL_JNI_STATIC_METHOD_JAVA_PTR_H
#define ISCOOL_JNI_STATIC_METHOD_JAVA_PTR_H

#include <iscool/jni/detail/static_method_base.hpp>
#include <iscool/jni/java_ptr.hpp>
#include <iscool/jni/static_method.hpp>

namespace iscool
{
  namespace jni
  {
    template <typename T>
    class static_method<java_ptr<T>> : public detail::static_method_base
    {
    public:
      using detail::static_method_base::static_method_base;

      template <typename... Arg>
      java_ptr<T> operator()(Arg&&... args) const;
    };
  }
}

#include <iscool/jni/detail/static_method_java_ptr.tpp>

#endif
