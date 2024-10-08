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
#include <iscool/files/file_exists.hpp>

#include <iscool/files/detail/system_delegates.hpp>

#include <cassert>

bool iscool::files::file_exists(const std::string& path)
{
  assert(detail::system_delegates != nullptr);
  return detail::system_delegates->file_exists(path);
}
