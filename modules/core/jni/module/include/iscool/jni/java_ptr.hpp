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
#ifndef ISCOOL_JNI_JAVA_PTR_H
#define ISCOOL_JNI_JAVA_PTR_H

#include <iscool/jni/detail/get_method_argument.hpp>

#include <cstdlib>

namespace iscool
{
  namespace jni
  {
    template <typename T>
    class java_ptr
    {
      template <typename U>
      friend class java_ptr;

    public:
      java_ptr();
      java_ptr(T value);
      java_ptr(const java_ptr<T>& that);
      java_ptr(java_ptr<T>&& that);

      template <typename U>
      java_ptr(const java_ptr<U>& that);

      ~java_ptr();

      void swap(java_ptr<T>& that);

      java_ptr<T>& operator=(const java_ptr<T>& that);
      java_ptr<T>& operator=(java_ptr<T>&& that);

      bool operator==(std::nullptr_t) const;
      bool operator!=(std::nullptr_t) const;

      T get() const;
      T release();

      T operator*() const;

    private:
      template <typename U>
      java_ptr(const java_ptr<U>& that, T value);

      void delete_java_ref();

    private:
      T _value;
      std::size_t* _counter;
    };

    namespace detail
    {
      template <typename T>
      struct get_method_argument_impl<java_ptr<T>>
      {
        static T get(const java_ptr<T>& arg);
      };
    }
  }
}

#include <iscool/jni/detail/java_ptr.tpp>

#endif
