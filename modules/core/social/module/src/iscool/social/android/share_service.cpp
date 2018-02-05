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
#include "iscool/social/android/share_service.h"

#include "iscool/jni/get_static_method.h"
#include "iscool/jni/new_java_string.h"
#include "iscool/jni/static_method_void.h"
#include "iscool/jni/string_bytes.h"

void iscool::social::android::share_service::share_message
( const std::string& message )
{
    const jni::static_method< void > method
        ( jni::get_static_method< void >
          ( "iscool/social/ShareService", "shareMessage", "([B)V" ) );

    method( jni::string_bytes( message ) );
}

void iscool::social::android::share_service::share_file
( const std::string& file_name, const std::string& message )
{
    const jni::static_method< void > method
        ( jni::get_static_method< void >
          ( "iscool/social/ShareService", "shareFile",
            "(Ljava/lang/String;[B)V" ) );

    method
        ( jni::new_java_string( file_name ), jni::string_bytes( message ) );
}
