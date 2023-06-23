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
#include <iscool/json/from_file.hpp>

#include <iscool/json/log_context.hpp>

#include <iscool/files/read_file.hpp>
#include <iscool/json/parse_stream.hpp>
#include <iscool/log/causeless_log.hpp>
#include <iscool/log/nature/error.hpp>

Json::Value iscool::json::from_file(const std::string& path)
{
  const std::unique_ptr<std::istream> file(files::read_file(path));
  const Json::Value result(parse_stream(*file));

  if (result == Json::nullValue)
    ic_causeless_log(iscool::log::nature::error(), log_context(),
                     "could not parse json file: %s", path);

  return result;
}
