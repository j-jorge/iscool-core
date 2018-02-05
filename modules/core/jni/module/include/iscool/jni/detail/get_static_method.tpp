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
#ifndef ISCOOL_JNI_GET_STATIC_METHOD_TPP
#define ISCOOL_JNI_GET_STATIC_METHOD_TPP

#include "iscool/jni/detail/get_static_method_info.h"

template< typename R >
iscool::jni::static_method< R > iscool::jni::get_static_method
( const char* class_name, const char* method_name, const char* signature )
{
    const detail::method_info m
        ( detail::get_static_method_info
          ( class_name, method_name, signature ) );
    return static_method< R >( m.env, m.class_id, m.method_id );
}

#endif
