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
#include "iscool/net/byte_array_bit_reader.h"

#include "iscool/net/byte_array_reader.h"

#include <limits.h>

static_assert
( CHAR_BIT == 8, "Only eight bits per byte platforms are supported." );

iscool::net::byte_array_bit_reader::byte_array_bit_reader
( byte_array_reader& array )
    : _array( array ),
      _available_bits( 0 )
{

}

std::uint8_t iscool::net::byte_array_bit_reader::get( std::uint8_t bit_count )
{
    if ( _available_bits == 0 )
        fill_buffer();

    const std::uint8_t direct_read( std::min( bit_count, _available_bits ) );
    const std::uint8_t direct_offset( _available_bits - direct_read );
    const std::uint8_t direct_mask
        ( ( ( 1 << direct_read ) - 1 ) << direct_offset );

    std::uint8_t result( ( _buffer & direct_mask ) >> direct_offset );

    if ( direct_read == bit_count )
        _available_bits -= direct_read;
    else
    {
        fill_buffer();
        
        const std::uint8_t next_read( bit_count - direct_read );
        const std::uint8_t next_offset( _available_bits - next_read );
        const std::uint8_t next_mask
            ( ( ( 1 << next_read ) - 1 ) << next_offset );

        result =
            ( result << next_read )
            | ( ( _buffer & next_mask ) >> next_offset );

        _available_bits = CHAR_BIT - next_read;
    }

    return result;
}

void iscool::net::byte_array_bit_reader::fill_buffer()
{
    _buffer = _array.get< std::uint8_t >();
    _available_bits = CHAR_BIT;
}
