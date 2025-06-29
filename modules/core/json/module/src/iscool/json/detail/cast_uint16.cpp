// SPDX-License-Identifier: Apache-2.0
#include <iscool/json/detail/cast_uint16.hpp>

#include <iscool/json/bad_cast.hpp>
#include <iscool/json/cast.impl.tpp>
#include <iscool/json/implement_cast.hpp>
#include <iscool/json/implement_is_of_type.hpp>
#include <iscool/json/is_of_type.hpp>
#include <iscool/json/is_of_type.impl.tpp>

#include <json/value.h>

IMPLEMENT_JSON_CAST(std::uint16_t)
IMPLEMENT_JSON_IS_OF_TYPE(std::uint16_t)

bool iscool::json::detail::cast<std::uint16_t>::is_valid(
    const Json::Value& value)
{
  if (value.isUInt())
    return value.asUInt64() <= 65535;

  if (!value.isInt())
    return false;

  const std::int64_t int_value(value.asInt64());

  return (0 <= int_value) && (int_value <= 65535);
}

std::uint16_t
iscool::json::detail::cast<std::uint16_t>::value(const Json::Value& value)
{
  if (!is_valid(value))
    throw bad_cast(value, "16 bits unsigned int");

  return value.asUInt();
}
