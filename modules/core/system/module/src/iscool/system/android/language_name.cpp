// SPDX-License-Identifier: Apache-2.0
#include <iscool/system/language_name.hpp>

#include <iscool/jni/get_static_method.hpp>
#include <iscool/jni/static_method_java_ptr.hpp>
#include <iscool/jni/to_string.hpp>

iscool::language_name iscool::system::get_language_name()
{
  const auto method(
      iscool::jni::get_static_method<iscool::jni::java_ptr<jstring>>(
          "iscool/system/SystemService", "getLanguageCode",
          "()Ljava/lang/String;"));

  return iscool::from_string_with_fallback(iscool::jni::to_string(method()));
}
