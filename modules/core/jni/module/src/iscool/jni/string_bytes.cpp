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
#include <iscool/jni/string_bytes.hpp>

#include <iscool/jni/detail/get_jni_env.hpp>

iscool::jni::java_ptr<jbyteArray>
iscool::jni::string_bytes(const std::string& str)
{
  JNIEnv* const env(detail::get_jni_env());

  const std::size_t size(str.size());
  const jbyteArray bytes(env->NewByteArray(size));
  env->SetByteArrayRegion(bytes, 0, size,
                          reinterpret_cast<const jbyte*>(str.c_str()));

  return java_ptr<jbyteArray>(bytes);
}
