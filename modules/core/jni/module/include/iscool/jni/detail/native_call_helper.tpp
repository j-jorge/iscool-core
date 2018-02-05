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
#ifndef ISCOOL_JNI_DETAIL_NATIVE_CALL_HELPER_TPP
#define ISCOOL_JNI_DETAIL_NATIVE_CALL_HELPER_TPP

#include "iscool/jni/detail/extract_argument.h"
#include "iscool/jni/detail/get_jni_env.h"

template< typename... Arg, std::size_t... I >
void
iscool::jni::detail::native_call_helper
<
    std::tuple< Arg... >,
    iscool::meta::indices< I... >
>
::call
( const boost::function< void( Arg... ) >& f,
  const java_ptr< jobjectArray >& arguments )
{
    JNIEnv* const env( detail::get_jni_env() );
    (void)env;
    
    f( extract_argument< I, std::tuple< Arg... > >( env, arguments )... );
}

#endif
