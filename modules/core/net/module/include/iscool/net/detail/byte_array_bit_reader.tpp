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
#include "iscool/meta/underlying_type.h"

#include <cassert>
#include <climits>

template< typename T >
T iscool::net::byte_array_bit_reader::get_large
( std::uint8_t bit_count )
{
    assert( bit_count / CHAR_BIT <= sizeof( T ) );
    
    typedef typename iscool::meta::underlying_type< T >::type raw_type;

    raw_type result( 0 );
    std::uint8_t isolated_bit_count( bit_count % CHAR_BIT );
    
    if ( isolated_bit_count != 0 )
    {
        result = get( isolated_bit_count );
        bit_count -= isolated_bit_count;
    }

    for ( ; bit_count > 0; bit_count -= CHAR_BIT )
        result = ( result << CHAR_BIT ) | raw_type( get( CHAR_BIT ) );
    
    return static_cast< T >( result );
}
