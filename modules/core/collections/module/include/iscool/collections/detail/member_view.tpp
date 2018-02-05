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
#ifndef ISCOOL_COLLECTIONS_MEMBER_VIEW_TPP
#define ISCOOL_COLLECTIONS_MEMBER_VIEW_TPP

template< typename R, typename T >
std::vector< R > iscool::collections::member_view
( const std::vector< T >& input, R ( T::*getter )() const )
{
    std::vector< R > result;
    result.reserve( input.size() );
    for ( const T& entry : input )
        result.push_back( ( entry.*getter )() );

    return result;
}

template< typename R, typename T >
std::vector< R > iscool::collections::member_view
( const std::vector< T >& input, R T::*field )
{
    std::vector< R > result;
    result.reserve( input.size() );
    for ( const T& entry : input )
        result.push_back( entry.*field );

    return result;
}

#endif
