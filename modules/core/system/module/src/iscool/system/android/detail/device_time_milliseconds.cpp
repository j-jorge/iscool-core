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
#include <iscool/system/detail/device_time_milliseconds.hpp>

#include <iscool/jni/get_static_method.hpp>
#include <iscool/jni/static_method_jlong.hpp>

std::chrono::milliseconds iscool::system::detail::device_time_milliseconds()
{
  const auto method(iscool::jni::get_static_method<jlong>(
      "iscool/system/SystemService", "getDeviceTime", "()J"));

  return std::chrono::milliseconds(method());
}
