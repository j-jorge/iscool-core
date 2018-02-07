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
#ifndef ISCOOL_JSON_DETAIL_CAST_VECTOR_TPP
#define ISCOOL_JSON_DETAIL_CAST_VECTOR_TPP

#include "iscool/json/bad_cast.h"

#include "json/value.h"

template< typename T >
bool
iscool::json::detail::cast< std::vector< T > >::is_valid
( const Json::Value& value )
{
    if ( !value.isArray() || value.isNull() )
        return false;

    const Json::ArrayIndex count( value.size() );

    for ( Json::ArrayIndex i( 0 ); i != count; ++i )
        if ( !cast< T >::is_valid( value[ i ] ) )
            return false;

    return true;
}

template< typename T >
std::vector< T >
iscool::json::detail::cast< std::vector< T > >::value
( const Json::Value& jsonValue )
{
    return value( jsonValue, &cast< T >::value );
}

template< typename T >
template< typename EntryCast >
std::vector< T >
iscool::json::detail::cast< std::vector< T > >::value
( const Json::Value& value, EntryCast entry_cast )
{
    if ( !value.isArray() || value.isNull() )
        throw bad_cast( value, "vector" );

    const Json::ArrayIndex count( value.size() );
    std::vector< T > result;
    result.reserve( count );

    for ( Json::ArrayIndex i( 0 ); i != count; ++i )
        result.push_back( entry_cast( value[ i ] ) );

    return result;
}

#endif
