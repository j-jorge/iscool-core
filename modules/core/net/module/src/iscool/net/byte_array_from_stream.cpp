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
#include "iscool/net/byte_array_from_stream.h"

#include <iostream>

iscool::net::byte_array iscool::net::byte_array_from_stream( std::istream& in )
{
    static constexpr std::size_t buffer_size( 2048 );

    char buffer[ buffer_size ];
    byte_array result;

    std::uint8_t* begin( reinterpret_cast< std::uint8_t* >( buffer ) );

    while( in )
    {
        in.read( buffer, buffer_size );
        result.append( begin, begin + in.gcount() );
    }

    return result;
}

