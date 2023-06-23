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
#include "iscool/resources/json/to_catalog.h"

#include "iscool/json/bad_cast.h"
#include "iscool/json/cast_string.h"
#include "iscool/json/cast_vector.h"
#include "iscool/log/log.h"

namespace iscool
{
  namespace resources
  {
    namespace detail
    {
      static std::vector<std::string> to_vector(const Json::Value& value);
    }
  }
}

iscool::resources::catalog
iscool::resources::json::to_catalog(const Json::Value& value)
{
  if (!value.isObject() || value.isNull())
    throw iscool::json::bad_cast(value, "object");

  return catalog(detail::to_vector(value["textures"]),
                 detail::to_vector(value["particles"]),
                 detail::to_vector(value["sounds"]),
                 detail::to_vector(value["styles"]));
}

std::vector<std::string>
iscool::resources::detail::to_vector(const Json::Value& value)
{
  if (value.isNull())
    return std::vector<std::string>();

  return iscool::json::cast<std::vector<std::string>>(value);
}
