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
#include "iscool/json/is_member.h"

#include <algorithm>

bool iscool::json::is_member( const std::string& key, Json::Value json_value )
{
    if ( json_value.type() != Json::objectValue )
        return false;

    const Json::Value::Members members( json_value.getMemberNames() );

    return std::find( members.begin(), members.end(), key ) != members.end();
}
