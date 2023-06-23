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
#ifndef ISCOOL_JNI_SCOPED_NATIVE_CALLBACK_H
#define ISCOOL_JNI_SCOPED_NATIVE_CALLBACK_H

#include <jni.h>

#include <functional>

namespace iscool
{
  namespace jni
  {
    enum class native_callback_lifespan;

    class scoped_native_callback
    {
    public:
      template <typename... Args>
      explicit scoped_native_callback(const std::function<void(Args...)>& f);

      ~scoped_native_callback();

      jlong get_id() const;

      scoped_native_callback(const scoped_native_callback&) = delete;
      scoped_native_callback&
      operator=(const scoped_native_callback&) = delete;

    private:
      const jlong _id;
    };
  }
}

#include <iscool/jni/detail/scoped_native_callback.tpp>

#endif
