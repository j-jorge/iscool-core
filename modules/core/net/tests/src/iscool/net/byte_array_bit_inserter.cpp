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

    inserter.append( 2 /* 10 */, 2 ); // 1000 0000
    inserter.append( 3 /* 11 */, 2 ); // 1011 0000
    inserter.append( 5 /* 101 */, 3 ); // 1011 1010
    inserter.append( 26 /* 11010*/, 5 ); // 1011 1011, 1010 0000

    inserter.flush();

    ASSERT_EQ( 2, array.size() );
    EXPECT_EQ( 0xbb, array[ 0 ] );
    EXPECT_EQ( 0xa0, array[ 1 ] );
}

TEST( iscool_net_byte_array_bit_inserter, flush_on_destroy )
{
    iscool::net::byte_array array;

    {
        iscool::net::byte_array_bit_inserter inserter( array );

        inserter.append( 2 /* 10 */, 2 ); // 1000 0000
        inserter.append( 3 /* 11 */, 2 ); // 1011 0000
        inserter.append( 5 /* 101 */, 3 ); // 1011 1010
        inserter.append( 26 /* 11010*/, 5 ); // 1011 1011, 1010 0000
    }
    
    ASSERT_EQ( 2, array.size() );
    EXPECT_EQ( 0xbb, array[ 0 ] );
    EXPECT_EQ( 0xa0, array[ 1 ] );
}
