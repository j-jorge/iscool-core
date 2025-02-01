// SPDX-License-Identifier: Apache-2.0
#include <iscool/system/keep_screen_on.hpp>

#include <iscool/jni/get_static_method.hpp>
#include <iscool/jni/static_method_void.hpp>

void iscool::system::keep_screen_on(bool keep_on)
{
  const auto method(iscool::jni::get_static_method<void>(
      "iscool/system/SystemService", "keepScreenOn", "(Z)V"));

  method(jboolean(keep_on));
}
