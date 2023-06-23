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
#include <iscool/files/delete_directory.hpp>

#include <iscool/files/log_context.hpp>

#include <iscool/log/causeless_log.hpp>
#include <iscool/log/nature/error.hpp>

#include <filesystem>

void iscool::files::delete_directory(const std::string& path)
{
  std::error_code error;
  std::filesystem::remove_all(path, error);

  if (error)
    ic_causeless_log(iscool::log::nature::error(), log_context(),
                     "Could not delete directory '%s': %s", path,
                     error.message());
}
