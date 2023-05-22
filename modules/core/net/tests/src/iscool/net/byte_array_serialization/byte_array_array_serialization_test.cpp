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
#include <gtest/gtest.h>

#include "iscool/net/byte_array.h"
#include "iscool/net/byte_array_reader.h"
#include "iscool/net/byte_array_serialization/byte_array_array_serialization.h"

TEST( byte_array_array_serialization_test, empty_array )
{
    iscool::net::byte_array output;
    output << std::array<std::uint8_t, 0>();

    iscool::net::byte_array_reader input( output );
    std::array<std::uint8_t, 0> v;
    input >> v;

    EXPECT_TRUE( v.empty() );
}

TEST( byte_array_array_serialization_test, non_empty )
{
    const std::array<std::uint8_t, 2> reference{ 1, 2 };

    iscool::net::byte_array output;
    output << reference;

    iscool::net::byte_array_reader input( output );
    std::array<std::uint8_t, 2> v;
    input >> v;

    EXPECT_EQ( reference, v );
}

TEST( byte_array_array_serialization_test, overwrites )
{
    const std::array<std::uint8_t, 2> reference{ 1, 2 };

    iscool::net::byte_array output;
    output << reference;

    iscool::net::byte_array_reader input( output );
    std::array<std::uint8_t, 2> v{ 2, 4 };
    input >> v;

    EXPECT_EQ( reference, v );
}

TEST( byte_array_array_serialization_test, between_values )
{
    const std::array<std::uint8_t, 2> reference{ 1, 2 };

    iscool::net::byte_array output;
    output << std::uint16_t( 0x0123 )
           << reference
           << std::uint32_t( 0x01234567 );

    iscool::net::byte_array_reader input( output );
    std::uint16_t a;
    std::array<std::uint8_t, 2> v;
    std::uint32_t b;
    input >> a >> v >> b;

    EXPECT_EQ( std::uint16_t( 0x0123 ), a );
    EXPECT_EQ( reference, v );
    EXPECT_EQ( std::uint32_t( 0x01234567 ), b );
}
