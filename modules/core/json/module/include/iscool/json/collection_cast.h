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
#ifndef ISCOOL_JSON_COLLECTION_CAST_H
#define ISCOOL_JSON_COLLECTION_CAST_H

namespace Json
{
  class Value;
}

namespace iscool
{
  namespace json
  {
    template <typename Collection>
    Collection collection_cast(const Json::Value& value);

    template <typename Collection, typename EntryCast>
    Collection collection_cast(const Json::Value& value, EntryCast entry_cast);
  }
}

#include "iscool/json/detail/collection_cast.tpp"

#endif
