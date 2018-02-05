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
#include "gtest/gtest.h"

#include <algorithm>

template< typename LeftContainer, typename RightContainer >
void iscool::test::assert_equal_collections
( LeftContainer left, RightContainer right, const std::string& message )
{
    ASSERT_EQ( std::distance( left.begin(), left.end() ),
               std::distance( right.begin(), right.end() ) )
        << message;

    bool are_equal( true );

    for ( auto item : left )
        if ( std::find( right.begin(), right.end(), item ) == right.end() )
        {
            are_equal = false;
            break;
        }

    ASSERT_TRUE( are_equal ) << message;
}
