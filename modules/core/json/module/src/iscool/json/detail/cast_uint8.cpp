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
#include <iscool/json/detail/cast_uint8.hpp>

#include <iscool/json/bad_cast.hpp>
#include <iscool/json/cast.impl.tpp>
#include <iscool/json/implement_cast.hpp>
#include <iscool/json/implement_is_of_type.hpp>
#include <iscool/json/is_of_type.hpp>
#include <iscool/json/is_of_type.impl.tpp>

#include <json/value.h>

IMPLEMENT_JSON_CAST(std::uint8_t)
IMPLEMENT_JSON_IS_OF_TYPE(std::uint8_t)

bool iscool::json::detail::cast<std::uint8_t>::is_valid(
    const Json::Value& value)
{
  if (value.isUInt())
    return value.asUInt64() <= 255;

  if (!value.isInt())
    return false;

  const std::int64_t int_value(value.asInt64());

  return (0 <= int_value) && (int_value <= 255);
}

std::uint8_t
iscool::json::detail::cast<std::uint8_t>::value(const Json::Value& value)
{
  if (!is_valid(value))
    throw bad_cast(value, "8 bits unsigned int");

  return value.asUInt();
}
