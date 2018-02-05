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
#ifndef ISCOOL_JNI_DETAIL_VARIADIC_NATIVE_CALLBACK_H
#define ISCOOL_JNI_DETAIL_VARIADIC_NATIVE_CALLBACK_H

#include "iscool/jni/detail/native_callback.h"

namespace iscool
{
    namespace jni
    {
        namespace detail
        {
            template< typename... Args >
            class variadic_native_callback:
                public native_callback
            {
                typedef boost::function< void( Args... ) > callback_type;
                
            public:
                variadic_native_callback
                ( native_callback_lifespan lifespan,
                  const callback_type& callback );

                void operator()
                ( const java_ptr<jobjectArray>& arguments ) override;
                
            private:
                template< std::size_t... I, typename... Arg >
                void execute_callback
                ( const java_ptr<jobjectArray>& arguments ) const;
                
            private:
                callback_type _callback;
            };
        }
    }
}

#include "iscool/jni/detail/variadic_native_callback.tpp"

#endif
