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
#include "iscool/json/bad_cast.h"

#include <json/value.h>

iscool::json::bad_cast::bad_cast(const Json::Value& value,
                                 const std::string& expected)
  : _message("Json value is not a valid " + expected + ": "
             + value.toStyledString())
{}

const char* iscool::json::bad_cast::what() const noexcept
{
  return _message.c_str();
}
