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
#include <iscool/preferences/detail/local_preferences_from_json.hpp>

#include <iscool/preferences/log_context.hpp>

#include <iscool/json/cast_bool.hpp>
#include <iscool/json/cast_int64.hpp>
#include <iscool/json/cast_string.hpp>
#include <iscool/json/is_of_type_bool.hpp>
#include <iscool/json/is_of_type_int64.hpp>
#include <iscool/json/is_of_type_string.hpp>
#include <iscool/log/log.hpp>
#include <iscool/log/nature/error.hpp>
#include <iscool/preferences/property_map.impl.hpp>

#include <json/value.h>

iscool::preferences::property_map
iscool::preferences::detail::local_preferences_from_json(
    const Json::Value& values)
{
  property_map result;

  if (!values.isObject())
    {
      ic_log(iscool::log::nature::error(), log_context(),
             "Property map cannot be built from non object: %s",
             values.toStyledString());
      return result;
    }

  for (const std::string& m : values.getMemberNames())
    {
      const Json::Value member(values[m]);

      if (iscool::json::is_of_type<std::int64_t>(member))
        result.set(m, iscool::json::cast<std::int64_t>(member));
      else if (iscool::json::is_of_type<bool>(member))
        result.set(m, iscool::json::cast<bool>(member));
      else if (iscool::json::is_of_type<std::string>(member))
        result.set(m, iscool::json::cast<std::string>(member));
      else
        ic_log(iscool::log::nature::error(), log_context(),
               "Property map cannot store value: %s", member.toStyledString());
    }

  return result;
}
