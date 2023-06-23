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
#include <iscool/jni/new_java_string.hpp>

#include <iscool/jni/detail/get_jni_env.hpp>

iscool::jni::java_ptr<jstring> iscool::jni::new_java_string(const char* str)
{
  JNIEnv* const env(detail::get_jni_env());
  return java_ptr<jstring>(env->NewStringUTF(str));
}

iscool::jni::java_ptr<jstring>
iscool::jni::new_java_string(const std::string& str)
{
  return new_java_string(str.c_str());
}
