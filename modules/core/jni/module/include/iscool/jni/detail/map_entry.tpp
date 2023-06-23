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
#ifndef ISCOOL_JNI_MAP_ENTRY_TPP
#define ISCOOL_JNI_MAP_ENTRY_TPP

#include "iscool/jni/get_method.h"
#include "iscool/jni/method_jobject.h"

template <typename K, typename V>
iscool::jni::map_entry<K, V>::map_entry(const java_ptr<jobject>& impl)
  : _impl(impl)
{}

template <typename K, typename V>
iscool::jni::map_entry<K, V>::map_entry(jobject impl)
  : _impl(impl)
{}

template <typename K, typename V>
iscool::jni::java_ptr<jobject>
iscool::jni::map_entry<K, V>::get_java_object() const
{
  return _impl;
}

template <typename K, typename V>
K iscool::jni::map_entry<K, V>::get_key() const
{
  const auto method(get_method<jobject>("java/util/Map$Entry", "getKey",
                                        "()Ljava/lang/Object;"));

  return K(method(_impl));
}

template <typename K, typename V>
V iscool::jni::map_entry<K, V>::get_value() const
{
  const auto method(get_method<jobject>("java/util/Map$Entry", "getValue",
                                        "()Ljava/lang/Object;"));

  return V(method(_impl));
}

template <typename K, typename V>
jobject iscool::jni::detail::get_method_argument_impl<
    iscool::jni::map_entry<K, V>>::get(const map_entry<K, V>& c)
{
  return c.get_java_object().get();
}

#endif
