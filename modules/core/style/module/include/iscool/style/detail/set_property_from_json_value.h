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
#ifndef ISCOOL_STYLE_DETAIL_SET_PROPERTY_FROM_JSON_VALUE_H
#define ISCOOL_STYLE_DETAIL_SET_PROPERTY_FROM_JSON_VALUE_H

#include <string>

namespace Json
{
    class Value;
}

namespace iscool
{
    namespace style
    {
        class declaration;
        
        namespace detail
        {
            void set_property_from_json_value
            ( iscool::style::declaration& style, const std::string& key,
              const Json::Value& value );
        }
    }
}


#endif
