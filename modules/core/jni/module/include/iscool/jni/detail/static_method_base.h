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
#ifndef ISCOOL_JNI_DETAIL_STATIC_METHOD_BASE_H
#define ISCOOL_JNI_DETAIL_STATIC_METHOD_BASE_H

#include "iscool/jni/java_ptr.h"

namespace iscool
{
  namespace jni
  {
    namespace detail
    {
      class static_method_base
      {
      public:
        static_method_base(JNIEnv* env, const java_ptr<jclass>& class_id,
                           jmethodID method_id);

        JNIEnv* get_env() const;

      protected:
        JNIEnv* _env;
        java_ptr<jclass> _class;
        jmethodID _method;
      };
    }
  }
}

#endif
