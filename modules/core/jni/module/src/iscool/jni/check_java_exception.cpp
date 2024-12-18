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
#include <iscool/jni/check_java_exception.hpp>

#include <iscool/jni/get_method.hpp>
#include <iscool/jni/log_context.hpp>
#include <iscool/jni/method_jstring.hpp>
#include <iscool/jni/to_string.hpp>
#include <iscool/log/log.hpp>
#include <iscool/log/nature/error.hpp>

bool iscool::jni::check_java_exception()
{
  JNIEnv* const env(detail::get_jni_env());

  if (!env->ExceptionCheck())
    return true;

  const method<jstring> method(get_method<jstring>(
      "java/lang/Object", "toString", "()Ljava/lang/String;"));

  const std::string message(to_string(method((env->ExceptionOccurred()))));

  ic_log(iscool::log::nature::error(), log_context(), "Java Exception: {}",
         message);

  return false;
}
