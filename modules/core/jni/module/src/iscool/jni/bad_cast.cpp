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
#include <iscool/jni/bad_cast.hpp>

#include <iscool/jni/get_method.hpp>
#include <iscool/jni/method_jobject.hpp>
#include <iscool/jni/to_string.hpp>

iscool::jni::bad_cast::bad_cast(jobject value, const std::string& expected)
{
  std::string cpp_string;

  if (value != nullptr)
    {
      const auto jobject_to_string(jni::get_method<jobject>(
          "java.lang.Object", "toString", "()Ljava/lang/String;"));

      jstring java_string((jstring)jobject_to_string(value));
      cpp_string = to_string(java_string);
    }
  else
    cpp_string = "nullptr";

  _message = "JNI value is not a valid " + expected + ": " + cpp_string;
}

const char* iscool::jni::bad_cast::what() const noexcept
{
  return _message.c_str();
}
