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
#include "iscool/style/json/to_declaration.h"

#include "iscool/style/log_context.h"

#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/error.h"
#include "iscool/style/detail/set_property_from_json_value.h"

#include "lib_json/value.h"

iscool::style::declaration
iscool::style::json::to_declaration( const Json::Value& value )
{
    declaration result;
    if( !value.isObject() )
    {
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "value is not a json object." );
        return result;
    }

    for( const std::string& name: value.getMemberNames() )
        if( name.empty() )
            ic_causeless_log
                ( iscool::log::nature::error(), log_context(),
                  "the name cannot be emtpy." );
        else
            detail::set_property_from_json_value( result, name, value[ name ] );

    return result;
}
