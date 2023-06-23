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
#include "iscool/files/test/file_system_delegates_mockup.h"

#include <filesystem>

#include <fstream>

iscool::files::test::file_system_delegates_mockup::
    file_system_delegates_mockup()
  : read_file_impl(
      [](const std::string& path) -> std::unique_ptr<std::istream>
      {
        return std::unique_ptr<std::istream>(new std::ifstream(path));
      })
  , get_writable_path_impl(
        []() -> std::string
        {
          return std::filesystem::temp_directory_path().string();
        })
  , file_exists_impl(
        [](const std::string& path) -> bool
        {
          const std::ifstream check(path);
          return check.good();
        })
  , get_full_path_impl(
        [](const std::string& path) -> std::string
        {
          return path;
        })
{}

std::unique_ptr<std::istream>
iscool::files::test::file_system_delegates_mockup::read_file(
    const std::string& path) const
{
  return read_file_impl(path);
}

std::string
iscool::files::test::file_system_delegates_mockup::get_writable_path() const
{
  return get_writable_path_impl();
}

bool iscool::files::test::file_system_delegates_mockup::file_exists(
    const std::string& path) const
{
  return file_exists_impl(path);
}

std::string iscool::files::test::file_system_delegates_mockup::get_full_path(
    const std::string& path) const
{
  return get_full_path_impl(path);
}

const iscool::files::file_system_delegates&
iscool::files::test::default_file_system_delegates_mockup()
{
  static const file_system_delegates_mockup result;
  return result;
}
