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
#include "iscool/system/send_to_background.h"

#include "iscool/jni/get_static_method.h"
#include "iscool/jni/static_method_void.h"

void iscool::system::send_to_background()
{
  const auto method(iscool::jni::get_static_method<void>(
      "iscool/system/SystemService", "sendToBackground", "()V"));

  method();
}
