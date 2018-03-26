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
#include "iscool/random/distinct_random.h"
#include "iscool/random/distinct_random.impl.tpp"

#include <gtest/gtest.h>

#include <unordered_set>

TEST( iscool_random_generator, empty )
{
    EXPECT_TRUE( iscool::random::distinct_random( 0, 10, 20 ).empty() );
}

TEST( iscool_random_generator, positive )
{
    const std::vector< int > values
        ( iscool::random::distinct_random( 5, 10, 20 ) );

    EXPECT_EQ( 5, values.size() );
    EXPECT_EQ
        ( 5, std::unordered_set< int >( values.begin(), values.end() ).size() );
}

TEST( iscool_random_generator, positive_all )
{
    const std::vector< int > values
        ( iscool::random::distinct_random( 100, 0, 99 ) );

    EXPECT_EQ( 100, values.size() );
    EXPECT_EQ
        ( 100,
          std::unordered_set< int >( values.begin(), values.end() ).size() );
}

TEST( iscool_random_generator, negative )
{
    const std::vector< int > values
        ( iscool::random::distinct_random( 5, -10, 20 ) );

    EXPECT_EQ( 5, values.size() );
    EXPECT_EQ
        ( 5, std::unordered_set< int >( values.begin(), values.end() ).size() );
}

TEST( iscool_random_generator, negative_all )
{
    const std::vector< int > values
        ( iscool::random::distinct_random( 31, -10, 20 ) );

    EXPECT_EQ( 31, values.size() );
    EXPECT_EQ
        ( 31,
          std::unordered_set< int >( values.begin(), values.end() ).size() );
}

TEST( iscool_random_generator, chars )
{
    const std::vector< char > values
        ( iscool::random::distinct_random( 26, 'a', 'z' ) );
    const std::vector< char > expected
        ( {
            'a', 'b', 'c', 'd', 'e',
            'f', 'g', 'h', 'i', 'j',
            'k', 'l', 'm', 'n', 'o',
            'p', 'q', 'r', 's', 't',
            'u', 'v', 'w', 'x', 'y',
            'z'
        } );

    EXPECT_EQ( expected, values );
}
