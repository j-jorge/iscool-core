// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/json/cast.hpp>
#include <iscool/json/detail/cast_fwd.hpp>

#include <json/value.h>

template <typename T>
T iscool::json::cast(const Json::Value& value)
{
  return detail::cast<T>::value(value);
}

template <typename T>
T iscool::json::cast(const Json::Value& value, const T& fallback)
{
  if (value.isNull())
    return fallback;

  return cast<T>(value);
}

template <typename T>
T iscool::json::member_cast(const Json::Value& value, std::string_view key)
{
  if (value.type() != Json::objectValue)
    throw bad_cast(value, "object");

  const Json::Value* const m = value.find(key.begin(), key.end());

  return detail::cast<T>::value(*m);
}
