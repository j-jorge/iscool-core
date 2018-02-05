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
#ifndef ISCOOL_JNI_DETAIL_EXTRACT_ARGUMENT_TPP
#define ISCOOL_JNI_DETAIL_EXTRACT_ARGUMENT_TPP

#include "iscool/jni/detail/extract_argument.h"
#include "iscool/jni/cast.h"

template< std::size_t I, typename Tuple >
typename std::decay
<
    typename std::tuple_element< I, Tuple >::type
>::type
iscool::jni::detail::extract_argument
( JNIEnv* env, const java_ptr< jobjectArray >& arguments )
{
    assert( env != nullptr );
    
    return
        iscool::jni::cast
        <
            typename std::decay
            <
                typename std::tuple_element< I, Tuple >::type
            >::type
        >
        ( env->GetObjectArrayElement( *arguments, I ) );
}

#endif
