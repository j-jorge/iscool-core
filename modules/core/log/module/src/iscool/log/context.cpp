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
#include <iscool/log/context.hpp>

iscool::log::context::context() = default;

iscool::log::context::context(const std::string& reporter,
                              const std::string origin,
                              const std::string& file, std::size_t line)
  : _reporter(reporter)
  , _origin(origin)
  , _file(file)
  , _line(line)
{}

iscool::log::context::~context() = default;

const std::string& iscool::log::context::get_reporter() const
{
  return _reporter;
}

const std::string& iscool::log::context::get_origin() const
{
  return _origin;
}

const std::string& iscool::log::context::get_file() const
{
  return _file;
}

std::size_t iscool::log::context::get_line() const
{
  return _line;
}
