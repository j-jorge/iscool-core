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
#include "iscool/style/json/from_declaration.h"

#include "iscool/style/declaration.h"
#include "iscool/style/detail/merge_declarations.h"

Json::Value iscool::style::json::from_declaration
( const iscool::style::declaration& style )
{
    Json::Value result( Json::objectValue );
    
    for ( const auto& e : style.get_numbers() )
        result[ e.first ] = e.second;

    for ( const auto& e : style.get_booleans() )
        result[ e.first ] = e.second;

    for ( const auto& e : style.get_strings() )
        result[ e.first ] = e.second;

    for ( const auto& e : style.get_declarations() )
        result[ e.first ][ 0 ] = from_declaration( e.second );

    return result;
}

