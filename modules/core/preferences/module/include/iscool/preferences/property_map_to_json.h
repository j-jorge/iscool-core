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
#ifndef ISCOOL_PREFERENCES_PROPERTY_MAP_TO_JSON_H
#define ISCOOL_PREFERENCES_PROPERTY_MAP_TO_JSON_H

#include "iscool/preferences/property_map.h"

#include <json/value.h>

namespace iscool
{
  namespace preferences
  {
    class property_map_to_json
    {
    public:
      explicit property_map_to_json(Json::Value& target);

      void operator()(const std::string& key, std::int64_t value);
      void operator()(const std::string& key, bool value);
      void operator()(const std::string& key, float value);
      void operator()(const std::string& key, const std::string& value);

    private:
      template <typename T>
      void insert(const std::string& key, const T& value);

    private:
      Json::Value& _target;
    };
  }
}

#endif
