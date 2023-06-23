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
#include <iscool/json/parse_string.hpp>

#include <iscool/json/log_context.hpp>

#include <iscool/log/causeless_log.hpp>
#include <iscool/log/nature/error.hpp>

#include <json/reader.h>

#include <memory>

Json::Value iscool::json::parse_string(const std::string& string)
{
  Json::CharReaderBuilder builder;
  builder.strictMode(&builder.settings_);

  const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

  const char* const begin(string.data());
  const char* const end(begin + string.size());

  std::string errors;
  Json::Value result;

  if (!reader->parse(begin, end, &result, &errors))
    {
      ic_causeless_log(iscool::log::nature::error(), log_context(), "%s",
                       errors);
      return Json::nullValue;
    }

  return result;
}
