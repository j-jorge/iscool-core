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
#ifndef ISCOOL_JNI_ITERATOR_TPP
#define ISCOOL_JNI_ITERATOR_TPP

#include "iscool/jni/get_method.h"
#include "iscool/jni/method_java_ptr.h"
#include "iscool/jni/method_jboolean.h"

template <typename T>
iscool::jni::iterator<T>::iterator(jobject impl)
  : _impl(impl)
{}

template <typename T>
iscool::jni::java_ptr<jobject>
iscool::jni::iterator<T>::get_java_object() const
{
  return _impl;
}

template <typename T>
bool iscool::jni::iterator<T>::has_next() const
{
  const auto method(
      get_method<jboolean>("java/util/Iterator", "hasNext", "()Z"));

  return method(_impl);
}

template <typename T>
typename iscool::jni::iterator<T>::value_type
iscool::jni::iterator<T>::next() const
{
  const auto method(get_method<java_ptr<jobject>>("java/util/Iterator", "next",
                                                  "()Ljava/lang/Object;"));

  return method(_impl);
}

template <typename T>
jobject
iscool::jni::detail::get_method_argument_impl<iscool::jni::iterator<T>>::get(
    const iterator<T>& i)
{
  return i.get_java_object().get();
}

#endif
