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
#ifndef ISCOOL_JSON_DETAIL_CAST_ARRAY_TPP
#define ISCOOL_JSON_DETAIL_CAST_ARRAY_TPP

#include "iscool/json/bad_cast.h"

#include "json/value.h"

template <typename T, std::size_t N>
bool iscool::json::detail::cast<std::array<T, N>>::is_valid(
    const Json::Value& value)
{
  if (!value.isArray() || value.isNull())
    return false;

  const Json::ArrayIndex count(value.size());

  if (count != Json::ArrayIndex(N))
    return false;

  for (std::size_t i(0); i != N; ++i)
    if (!cast<T>::is_valid(value[Json::ArrayIndex(i)]))
      return false;

  return true;
}

template <typename T, std::size_t N>
std::array<T, N> iscool::json::detail::cast<std::array<T, N>>::value(
    const Json::Value& json_value)
{
  return value(json_value, &cast<T>::value);
}

template <typename T, std::size_t N>
template <typename EntryCast>
std::array<T, N>
iscool::json::detail::cast<std::array<T, N>>::value(const Json::Value& value,
                                                    EntryCast entry_cast)
{
  if (!value.isArray() || value.isNull())
    throw bad_cast(value, "array");

  const Json::ArrayIndex count(value.size());

  if (count != N)
    throw bad_cast(value, "array");

  std::array<T, N> result;

  for (std::size_t i(0); i != N; ++i)
    result[i] = entry_cast(value[Json::ArrayIndex(i)]);

  return result;
}

#endif
