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
#include "iscool/json/detail/cast_float.h"

#include "iscool/json/bad_cast.h"
#include "iscool/json/cast.impl.tpp"
#include "iscool/json/implement_cast.h"
#include "iscool/json/implement_is_of_type.h"
#include "iscool/json/is_of_type.h"
#include "iscool/json/is_of_type.impl.tpp"

#include <json/value.h>

IMPLEMENT_JSON_CAST(float)
IMPLEMENT_JSON_IS_OF_TYPE(float)

bool iscool::json::detail::cast<float>::is_valid(const Json::Value& value)
{
  return value.isDouble() || value.isInt() || value.isUInt();
}

float iscool::json::detail::cast<float>::value(const Json::Value& value)
{
  if (!is_valid(value))
    throw bad_cast(value, "float");

  return value.asFloat();
}
