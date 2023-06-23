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
#ifndef ISCOOL_JNI_ARRAY_LIST_TPP
#define ISCOOL_JNI_ARRAY_LIST_TPP

#include <iscool/jni/alloc.hpp>
#include <iscool/jni/get_method.hpp>
#include <iscool/jni/method_jboolean.hpp>

template <typename T>
iscool::jni::array_list<T>::array_list()
  : _array(alloc("java/util/ArrayList", "()V"))
{}

template <typename T>
iscool::jni::java_ptr<jobject>
iscool::jni::array_list<T>::get_java_object() const
{
  return _array;
}

template <typename T>
jboolean iscool::jni::array_list<T>::add(const value_type& value) const
{
  const auto method(get_method<jboolean>("java/util/ArrayList", "add",
                                         "(Ljava/lang/Object;)Z"));

  return method(_array, value);
}

template <typename T>
jobject
iscool::jni::detail::get_method_argument_impl<iscool::jni::array_list<T>>::get(
    const array_list<T>& array)
{
  return array.get_java_object().get();
}

#endif
