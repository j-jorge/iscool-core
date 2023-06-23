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
#include "iscool/jni/throw_java_exception.h"

#include "iscool/jni/detail/get_jni_env.h"
#include "iscool/jni/get_class.h"
#include "iscool/jni/new_java_string.h"
#include "iscool/strings/format.h"

void iscool::jni::throw_java_exception(const std::string& type,
                                       const std::string& what)
{
  const java_ptr<jclass> class_id(get_class(type.c_str()));

  if (class_id.get() != nullptr)
    detail::get_jni_env()->ThrowNew(class_id.get(), what.c_str());
  else
    throw_java_exception(iscool::strings::format(
        "Invalid exception type( %s ): %s", type, what));
}

void iscool::jni::throw_java_exception(const std::string& what)
{
  const java_ptr<jclass> class_id(get_class("java/lang/Error"));
  detail::get_jni_env()->ThrowNew(class_id.get(), what.c_str());
}
