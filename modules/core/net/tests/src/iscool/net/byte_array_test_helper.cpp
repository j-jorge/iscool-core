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
#include "iscool/net/byte_array_test_helper.h"

#include "gtest/gtest.h"

iscool::net::byte_array
iscool::net::tests::std_string_to_byte_array( const std::string& string )
{
    iscool::net::byte_array result;
    for( char character: string )
        result.append< std::uint8_t >( character );

    return result;
}

void iscool::net::tests::expect_eq
( const iscool::net::byte_array& first, const iscool::net::byte_array& second )
{
    ASSERT_EQ( first.size(), second.size() );
    EXPECT_TRUE( std::equal( first.begin(), first.end(), second.begin() ) );
}
