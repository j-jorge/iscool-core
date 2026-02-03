// SPDX-License-Identifier: Apache-2.0
#include <iscool/json/detail/cast_int8.hpp>

#include <iscool/json/bad_cast.hpp>
#include <iscool/json/cast.impl.tpp>
#include <iscool/json/implement_cast.hpp>
#include <iscool/json/implement_is_of_type.hpp>
#include <iscool/json/is_of_type.hpp>
#include <iscool/json/is_of_type.impl.tpp>

#include <json/value.h>

IMPLEMENT_JSON_CAST(std::int8_t)
IMPLEMENT_JSON_IS_OF_TYPE(std::int8_t)

bool iscool::json::detail::cast<std::int8_t>::is_valid(
    const Json::Value& value)
{
  if (value.isUInt())
    return value.asUInt64() <= std::numeric_limits<std::int8_t>::max();

  if (!value.isInt())
    return false;

  const std::int64_t int_value(value.asInt64());

  return (std::numeric_limits<std::int8_t>::min() <= int_value)
         && (int_value <= std::numeric_limits<std::int8_t>::max());
}

std::int8_t
iscool::json::detail::cast<std::int8_t>::value(const Json::Value& value)
{
  if (!is_valid(value))
    throw bad_cast(value, "8 bits int");

  return value.asInt();
}
