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
#include "iscool/jni/cast_std_string.h"

#include "iscool/jni/bad_cast.h"
#include "iscool/jni/cast.impl.tpp"
#include "iscool/jni/implement_cast.h"
#include "iscool/jni/get_method.h"
#include "iscool/jni/method_jstring.h"
#include "iscool/jni/to_string.h"

IMPLEMENT_JNI_CAST( std::string );

std::string iscool::jni::detail::cast< std::string >::value( jobject object )
{
    const auto to_string_method
        ( jni::get_method< jstring >
          ( "java/lang/String", "toString", "()Ljava/lang/String;" ) );
    return iscool::jni::to_string( to_string_method( object ) );
}
