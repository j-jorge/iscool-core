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
#ifndef ISCOOL_JNI_DETAIL_SCOPED_NATIVE_CALLBACK_TPP
#define ISCOOL_JNI_DETAIL_SCOPED_NATIVE_CALLBACK_TPP

#include "iscool/jni/native_callback_lifespan.h"
#include "iscool/jni/register_native_callback.h"

template< typename... Args >
iscool::jni::scoped_native_callback::scoped_native_callback
( const boost::function< void( Args... ) >& f )
    : _id( register_native_callback( native_callback_lifespan::persistent, f ) )
{

}

#endif
