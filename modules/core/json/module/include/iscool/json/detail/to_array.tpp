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
#ifndef ISCOOL_JSON_TO_ARRAY_TPP
#define ISCOOL_JSON_TO_ARRAY_TPP

#include <iterator>

template< typename Iterator >
Json::Value
iscool::json::to_array( const Iterator& first, const Iterator& last )
{
    Json::Value result( Json::arrayValue );
    result.resize( std::distance( first, last ) );

    Json::ArrayIndex i( 0 );
    
    for ( Iterator it( first ); it != last; ++it, ++i )
        result[ i ] = *it;

    return result;
}

#endif
