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
#ifndef ISCOOL_JSON_DETAIL_CAST_UNORDERED_MAP_TPP
#define ISCOOL_JSON_DETAIL_CAST_UNORDERED_MAP_TPP

#include "iscool/json/bad_cast.h"

#include "json/value.h"

template <typename K, typename V>
bool iscool::json::detail::cast<std::unordered_map<K, V>>::is_valid(
    const Json::Value& value)
{
  if (!value.isArray() || value.isNull())
    return false;

  for (const Json::Value& entry : value)
    {
      const Json::Value& key(entry["key"]);
      const Json::Value& value(entry["value"]);

      if (!cast<K>::is_valid(key) || !cast<V>::is_valid(value))
        return false;
    }

  return true;
}

template <typename K, typename V>
std::unordered_map<K, V>
iscool::json::detail::cast<std::unordered_map<K, V>>::value(
    const Json::Value& value)
{
  if (!value.isArray() || value.isNull())
    throw bad_cast(value, "array");

  std::unordered_map<K, V> result;
  result.reserve(value.size());

  for (const Json::Value& entry : value)
    {
      if (!entry.isObject() || entry.isNull())
        throw iscool::json::bad_cast(entry, "object");

      result.emplace(cast<K>::value(entry["key"]),
                     cast<V>::value(entry["value"]));
    }

  return result;
}

#endif
