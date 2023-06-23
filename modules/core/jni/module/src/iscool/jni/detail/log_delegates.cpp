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
#include "iscool/jni/detail/log_delegates.h"

#include "iscool/jni/detail/native_call.h"
#include "iscool/jni/get_static_method.h"
#include "iscool/jni/native_callback_lifespan.h"
#include "iscool/jni/register_native_callback.h"
#include "iscool/jni/static_method_void.h"

#include "iscool/log/log.h"
#include "iscool/log/nature/debug.h"
#include "iscool/log/nature/error.h"
#include "iscool/log/nature/info.h"
#include "iscool/log/nature/nature.h"
#include "iscool/log/nature/warning.h"

namespace iscool
{
  namespace jni
  {
    namespace detail
    {
      static void java_log(int level, const std::string& tag,
                           const std::string& message);

      static jlong java_to_native_log;
    }
  }
}

void iscool::jni::detail::setup_log_delegates()
{
  java_to_native_log = register_native_callback(
      native_callback_lifespan::persistent,
      std::function<void(int, const std::string&, const std::string&)>(
          &java_log));

  static_method<void> method(
      get_static_method<void>("iscool/jni/NativeLog", "nativeReady", "(J)V"));

  method(java_to_native_log);
}

void iscool::jni::detail::finalize_log_delegates()
{
  static_method<void> method(
      get_static_method<void>("iscool/jni/NativeLog", "nativeReady", "(J)V"));

  method(0);
}

void iscool::jni::detail::java_log(int level, const std::string& tag,
                                   const std::string& message)
{
  const iscool::log::nature::nature* nature;

  switch (level)
    {
    case 3:
      nature = &iscool::log::nature::debug();
      break;
    case 5:
      nature = &iscool::log::nature::warning();
      break;
    case 6:
      nature = &iscool::log::nature::error();
      break;
    default:
      nature = &iscool::log::nature::info();
    }

  ic_log(*nature, tag, "Java", "%1%", message);
}
