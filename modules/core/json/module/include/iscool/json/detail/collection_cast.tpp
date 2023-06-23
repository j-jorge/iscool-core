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
#ifndef ISCOOL_JSON_COLLECTION_CAST_TPP
#define ISCOOL_JSON_COLLECTION_CAST_TPP

#include <iscool/json/detail/cast_fwd.hpp>

template <typename Collection>
Collection iscool::json::collection_cast(const Json::Value& value)
{
  static const auto default_cast(
      [](const Json::Value& v) -> typename Collection::value_type
      {
        return iscool::json::cast<typename Collection::value_type>(v);
      });

  return collection_cast<Collection>(value, default_cast);
}

template <typename Collection, typename EntryCast>
Collection iscool::json::collection_cast(const Json::Value& value,
                                         EntryCast entry_cast)
{
  return detail::cast<Collection>::value(value, entry_cast);
}

#endif
