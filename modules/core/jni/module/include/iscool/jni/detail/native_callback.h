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
#ifndef ISCOOL_JNI_DETAIL_NATIVE_CALLBACK_H
#define ISCOOL_JNI_DETAIL_NATIVE_CALLBACK_H

#include "iscool/jni/java_ptr.h"

#include <jni.h>

namespace iscool
{
    namespace jni
    {
        enum class native_callback_lifespan;
            
        namespace detail
        {
            class native_callback
            {
            public:
                explicit native_callback( native_callback_lifespan lifespan );
                virtual ~native_callback();

                virtual void operator()
                ( const java_ptr< jobjectArray >& arguments ) = 0;

                native_callback_lifespan get_lifespan() const;
                
            private:
                const native_callback_lifespan _lifespan;
            };
        }
    }
}

#endif
