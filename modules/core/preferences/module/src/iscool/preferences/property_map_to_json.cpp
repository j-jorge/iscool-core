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
#include "iscool/preferences/property_map_to_json.h"

iscool::preferences::property_map_to_json::property_map_to_json(
    Json::Value& target)
  : _target(target)
{}

void iscool::preferences::property_map_to_json::operator()(
    const std::string& key, std::int64_t value)
{
  insert(key, value);
}

void iscool::preferences::property_map_to_json::operator()(
    const std::string& key, bool value)
{
  insert(key, value);
}

void iscool::preferences::property_map_to_json::operator()(
    const std::string& key, float value)
{
  insert(key, value);
}

void iscool::preferences::property_map_to_json::operator()(
    const std::string& key, const std::string& value)
{
  insert(key, value);
}

template <typename T>
void iscool::preferences::property_map_to_json::insert(const std::string& key,
                                                       const T& value)
{
  _target[key] = value;
}
