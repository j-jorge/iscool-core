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
#include <iscool/jni/detail/get_static_method_info.hpp>

#include <iscool/jni/detail/get_jni_env.hpp>
#include <iscool/jni/get_class.hpp>
#include <iscool/jni/method_not_found.hpp>

iscool::jni::detail::method_info iscool::jni::detail::get_static_method_info(
    const char* class_name, const char* method_name, const char* signature)
{
  JNIEnv* const env(detail::get_jni_env());

  const java_ptr<jclass> class_id(get_class(class_name));
  const jmethodID method_id(
      env->GetStaticMethodID(class_id.get(), method_name, signature));

  if (!method_id)
    throw method_not_found(std::string("static method not found: ")
                           + class_name + "." + method_name + signature);

  return method_info{ env, class_id, method_id };
}
