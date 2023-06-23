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
#include <iscool/jni/get_class.hpp>

#include <iscool/jni/class_not_found.hpp>
#include <iscool/jni/detail/get_jni_env.hpp>
#include <iscool/jni/detail/log_delegates.hpp>
#include <iscool/jni/method_jclass.hpp>
#include <iscool/jni/new_java_string.hpp>

namespace iscool
{
  namespace jni
  {
    namespace detail
    {
      static jclass get_java_class(const char* class_name);
      static jclass get_custom_class(const char* class_name);

      static void set_class_loader(JNIEnv* env, jobject class_loader);

      static java_ptr<jobject> class_loader;
      static jmethodID find_class_method;
    }
  }
}

iscool::jni::java_ptr<jclass> iscool::jni::get_class(const char* class_name)
{
  jclass result(detail::get_java_class(class_name));

  if (result == nullptr)
    result = detail::get_custom_class(class_name);

  if (!result)
    throw class_not_found(std::string("class not found: ") + class_name);

  return result;
}

jclass iscool::jni::detail::get_java_class(const char* class_name)
{
  JNIEnv* const env(detail::get_jni_env());
  const jclass result(env->FindClass(class_name));

  if (env->ExceptionCheck())
    env->ExceptionClear();

  return result;
}

jclass iscool::jni::detail::get_custom_class(const char* class_name)
{
  assert(iscool::jni::detail::class_loader != nullptr);
  assert(iscool::jni::detail::find_class_method != nullptr);

  const method<jclass> find_class(detail::get_jni_env(), find_class_method);

  const jclass result(find_class(class_loader, new_java_string(class_name)));

  return result;
}

void iscool::jni::detail::set_class_loader(JNIEnv* env, jobject class_loader)
{
  assert(iscool::jni::detail::class_loader == nullptr);

  iscool::jni::detail::class_loader = env->NewGlobalRef(class_loader);

  const jclass class_loader_class(env->GetObjectClass(class_loader));
  iscool::jni::detail::find_class_method =
      env->GetMethodID(class_loader_class, "findClass",
                       "(Ljava/lang/String;)Ljava/lang/Class;");
}

extern "C" void Java_iscool_jni_JniService_configure(JNIEnv* env, jobject obj,
                                                     jobject context)
{
  const jclass context_class(env->GetObjectClass(context));
  const jmethodID get_class_loader_method(env->GetMethodID(
      context_class, "getClassLoader", "()Ljava/lang/ClassLoader;"));
  const jobject class_loader(
      env->CallObjectMethod(context, get_class_loader_method));

  iscool::jni::detail::set_class_loader(env, class_loader);
  iscool::jni::detail::setup_log_delegates();
}
