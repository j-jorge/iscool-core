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
#include "iscool/net/byte_array_bit_inserter.h"

#include "iscool/net/byte_array.h"

#include <gtest/gtest.h>

TEST( iscool_net_byte_array_bit_inserter, append )
{
    iscool::net::byte_array array;
    iscool::net::byte_array_bit_inserter inserter( array );

    inserter.append( std::uint8_t( 2 ) /* 10 */, 2 ); // 1000 0000
    inserter.append( std::uint8_t( 3 )/* 11 */, 2 ); // 1011 0000
    inserter.append( std::uint8_t( 5 )/* 101 */, 3 ); // 1011 1010
    inserter.append( std::uint8_t( 26 ) /* 11010*/, 5 ); // 1011 1011, 1010 0000

    inserter.flush();

    ASSERT_EQ( 2, array.size() );
    EXPECT_EQ( 0xbb, array[ 0 ] );
    EXPECT_EQ( 0xa0, array[ 1 ] );
}


TEST( iscool_net_byte_array_bit_inserter, append_large )
{
    iscool::net::byte_array array;
    iscool::net::byte_array_bit_inserter inserter( array );

    inserter.append( std::uint8_t( 2 ) /* 10 */, 2 );
    // 1000 0000
    
    inserter.append
        ( std::uint16_t( 2469 )/* 1001 1010 0101 */, 12 );
    // 1010 0110 1001 0100
    
    inserter.append
        ( std::uint16_t( 9558 )/* 00100 0101 0101 0110 */, 11 );
    // 1010 0110 1001 0110 1010 1011 0000 0000

    inserter.flush();

    ASSERT_EQ( 4, array.size() );
    EXPECT_EQ( 0xa6, array[ 0 ] );
    EXPECT_EQ( 0x96, array[ 1 ] );
    EXPECT_EQ( 0xab, array[ 2 ] );
    EXPECT_EQ( 0x00, array[ 3 ] );
}

TEST( iscool_net_byte_array_bit_inserter, flush_on_destroy )
{
    iscool::net::byte_array array;

    {
        iscool::net::byte_array_bit_inserter inserter( array );

        inserter.append( std::uint8_t( 2 ) /* 10 */, 2 ); // 1000 0000
        inserter.append( std::uint8_t( 3 ) /* 11 */, 2 ); // 1011 0000
        inserter.append( std::uint8_t( 5 ) /* 101 */, 3 ); // 1011 1010
        inserter.append
            ( std::uint8_t( 26 ) /* 11010*/, 5 ); // 1011 1011, 1010 0000
    }
    
    ASSERT_EQ( 2, array.size() );
    EXPECT_EQ( 0xbb, array[ 0 ] );
    EXPECT_EQ( 0xa0, array[ 1 ] );
}
