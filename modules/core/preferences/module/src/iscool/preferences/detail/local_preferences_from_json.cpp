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
#include "iscool/preferences/detail/local_preferences_from_json.h"

#include "iscool/preferences/log_context.h"

#include "iscool/json/cast_int.h"
#include "iscool/json/cast_bool.h"
#include "iscool/json/cast_string.h"
#include "iscool/json/is_of_type_bool.h"
#include "iscool/json/is_of_type_int.h"
#include "iscool/json/is_of_type_string.h"
#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/error.h"
#include "iscool/preferences/property_map.impl.h"

#include <lib_json/value.h>

iscool::preferences::property_map
iscool::preferences::detail::local_preferences_from_json
( const Json::Value& values )
{
    property_map result;

    if ( !values.isObject() )
    {
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "Property map cannot be built from non object: %s",
              values.toStyledString() );
        return result;
    }
    
    for ( const std::string& m : values.getMemberNames() )
    {
        const Json::Value member( values[ m ] );
        
        if ( iscool::json::is_of_type< int >( member ) )
            result.set( m, iscool::json::cast< int >( member ) );
        else if ( iscool::json::is_of_type< bool >( member ) )
            result.set( m, iscool::json::cast< bool >( member ) );
        else if ( iscool::json::is_of_type< std::string >( member ) )
            result.set( m, iscool::json::cast< std::string >( member ) );
        else
            ic_causeless_log
                ( iscool::log::nature::error(), log_context(),
                  "Property map cannot store value: %s",
                  member.toStyledString() );
    }
    
    return result;
}

