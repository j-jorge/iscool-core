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
#include "iscool/jni/to_string.h"

#include "iscool/jni/detail/get_jni_env.h"

std::string iscool::jni::to_string( const java_ptr< jstring >& java_string )
{
    if ( java_string.get() == nullptr )
        return std::string();
        
    JNIEnv* const env( detail::get_jni_env() );

    const char* const chars
        ( env->GetStringUTFChars( java_string.get(), nullptr ) );
    const std::string result( chars );
    
    env->ReleaseStringUTFChars( java_string.get(), chars );

    return result;
}
