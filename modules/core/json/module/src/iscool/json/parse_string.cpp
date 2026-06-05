// SPDX-License-Identifier: Apache-2.0
#include <iscool/json/parse_string.hpp>

#include <iscool/json/log_context.hpp>

#include <iscool/log/log.hpp>
#include <iscool/log/nature/error.hpp>

#include <json/reader.h>

#include <memory>

Json::Value iscool::json::parse_string(std::string_view string)
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
      ic_log(iscool::log::nature::error(), log_context(), "{}", errors);
      return Json::nullValue;
    }

  return result;
}
