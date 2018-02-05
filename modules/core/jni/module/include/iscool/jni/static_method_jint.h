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
#ifndef ISCOOL_JNI_STATIC_METHOD_JINT_H
#define ISCOOL_JNI_STATIC_METHOD_JINT_H

#include "iscool/jni/static_method.h"
#include "iscool/jni/detail/static_method_base.h"

namespace iscool
{
    namespace jni
    {
        template<>
        class static_method< jint >:
            public detail::static_method_base
        {
        public:
            using detail::static_method_base::static_method_base;
            
            template< typename... Arg >
            jint operator()( Arg&&... args ) const;
        };
    }
}

#include "iscool/jni/detail/static_method_jint.tpp"

#endif
