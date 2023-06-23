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
#ifndef ISCOOL_JNI_JAVA_PTR_TPP
#define ISCOOL_JNI_JAVA_PTR_TPP

#include <iscool/jni/detail/get_jni_env.hpp>

#include <algorithm>
#include <cassert>

template <typename T>
iscool::jni::java_ptr<T>::java_ptr()
  : _value(nullptr)
  , _counter(nullptr)
{}

template <typename T>
iscool::jni::java_ptr<T>::java_ptr(T value)
  : _value(value)
  , _counter(nullptr)
{
  if (_value != nullptr)
    _counter = new std::size_t(0);
}

template <typename T>
iscool::jni::java_ptr<T>::java_ptr(const java_ptr<T>& that)
  : java_ptr<T>(that, that._value)
{}

template <typename T>
iscool::jni::java_ptr<T>::java_ptr(java_ptr<T>&& that)
  : _value(that._value)
  , _counter(that._counter)
{
  that._counter = nullptr;
}

template <typename T>
template <typename U>
iscool::jni::java_ptr<T>::java_ptr(const java_ptr<U>& that, T value)
  : _value(value)
  , _counter(that._counter)
{
  if (_counter != nullptr)
    ++(*_counter);
}

template <typename T>
template <typename U>
iscool::jni::java_ptr<T>::java_ptr(const java_ptr<U>& that)
  : java_ptr<T>(that, that.get())
{}

template <typename T>
iscool::jni::java_ptr<T>::~java_ptr()
{
  if (_counter == nullptr)
    return;

  if (*_counter == 0)
    {
      delete_java_ref();
      delete _counter;
      _counter = nullptr;
    }
  else
    --(*_counter);
}

template <typename T>
void iscool::jni::java_ptr<T>::swap(java_ptr<T>& that)
{
  std::swap(_value, that._value);
  std::swap(_counter, that._counter);
}

template <typename T>
iscool::jni::java_ptr<T>&
iscool::jni::java_ptr<T>::operator=(const java_ptr<T>& that)
{
  java_ptr<T> tmp(that);
  swap(tmp);
  return *this;
}

template <typename T>
iscool::jni::java_ptr<T>&
iscool::jni::java_ptr<T>::operator=(java_ptr<T>&& that)
{
  swap(that);
  return *this;
}

template <typename T>
bool iscool::jni::java_ptr<T>::operator==(std::nullptr_t) const
{
  return _value == nullptr;
}

template <typename T>
bool iscool::jni::java_ptr<T>::operator!=(std::nullptr_t) const
{
  return _value != nullptr;
}

template <typename T>
T iscool::jni::java_ptr<T>::get() const
{
  return _value;
}

template <typename T>
T iscool::jni::java_ptr<T>::release()
{
  if (_counter != nullptr)
    {
      assert(*_counter == 0);

      delete _counter;
      _counter = nullptr;
    }
  else
    assert(_value == nullptr);

  return _value;
}

template <typename T>
T iscool::jni::java_ptr<T>::operator*() const
{
  return get();
}

template <typename T>
void iscool::jni::java_ptr<T>::delete_java_ref()
{
  assert(_value != nullptr);
  JNIEnv* const jni_env(detail::get_jni_env());

  const jobjectRefType reference_type(jni_env->GetObjectRefType(_value));
  if (reference_type == JNILocalRefType)
    jni_env->DeleteLocalRef(_value);
  else if (reference_type == JNIGlobalRefType)
    jni_env->DeleteGlobalRef(_value);
}

template <typename T>
T iscool::jni::detail::get_method_argument_impl<iscool::jni::java_ptr<T>>::get(
    const java_ptr<T>& arg)
{
  return arg.get();
}

#endif
