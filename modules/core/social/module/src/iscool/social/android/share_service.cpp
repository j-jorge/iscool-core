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
#include "iscool/social/android/share_service.h"

#include "iscool/files/delete_file.h"
#include "iscool/files/file_exists.h"
#include "iscool/files/get_writable_path.h"
#include "iscool/files/read_file.h"
#include "iscool/jni/get_static_method.h"
#include "iscool/jni/new_java_string.h"
#include "iscool/jni/static_method_void.h"
#include "iscool/jni/string_bytes.h"

#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/error.h"

#include <fstream>

namespace iscool
{
  namespace social
  {
    namespace android
    {
      namespace detail
      {
        static bool is_embedded_asset(const std::string& path);
        static std::string copy_asset(const std::string& path);
      }
    }
  }
}

iscool::social::android::share_service::~share_service()
{
  for (const std::string& file : _temp_files)
    if (iscool::files::file_exists(file))
      iscool::files::delete_file(file);
}

void iscool::social::android::share_service::share_message(
    const std::string& message)
{
  const iscool::jni::static_method<void> method(
      iscool::jni::get_static_method<void>("iscool/social/ShareService",
                                           "shareMessage", "([B)V"));

  method(iscool::jni::string_bytes(message));
}

void iscool::social::android::share_service::share_file(
    const std::string& file_name, const std::string& message)
{
  const iscool::jni::static_method<void> method(
      iscool::jni::get_static_method<void>("iscool/social/ShareService",
                                           "shareFile",
                                           "(Ljava/lang/String;[B)V"));

  const iscool::jni::java_ptr<jbyteArray> message_bytes(
      iscool::jni::string_bytes(message));

  if (detail::is_embedded_asset(file_name))
    {
      const std::string copied_file(detail::copy_asset(file_name));

      if (copied_file.empty())
        return;

      _temp_files.insert(copied_file);

      method(iscool::jni::new_java_string(copied_file), message_bytes);
    }
  else
    method(iscool::jni::new_java_string(file_name), message_bytes);
}

bool iscool::social::android::detail::is_embedded_asset(
    const std::string& path)
{
  static const char* assets_prefix("assets/");

  return std::strncmp(path.c_str(), assets_prefix, std::strlen(assets_prefix))
         == 0;
}

std::string
iscool::social::android::detail::copy_asset(const std::string& path)
{
  const std::string::size_type last_dot(path.find_last_of('.'));

  std::string extension;

  if (last_dot != std::string::npos)
    extension = path.substr(last_dot);

  const std::string result(iscool::files::get_writable_path() + "/shared-asset"
                           + extension);

  const std::unique_ptr<std::istream> input_file(
      iscool::files::read_file(path));

  if (!input_file)
    {
      ic_causeless_log(iscool::log::nature::error(),
                       "iscool::social::share_file",
                       "Could not read file '%1%'", path);
      return "";
    }

  std::ofstream copied_file(result, std::ios::binary);
  copied_file << input_file->rdbuf();

  return result;
}
