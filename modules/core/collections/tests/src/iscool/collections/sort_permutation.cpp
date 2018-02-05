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
#include "iscool/collections/sort_permutation.h"

#include <gtest/gtest.h>

TEST( iscool_collections_sort_permutations, empty )
{
    const std::vector< int > values( {} );

    const std::vector< std::size_t > indices
        ( iscool::collections::sort_permutation
          ( values.begin(), values.end() ) );

    EXPECT_TRUE( indices.empty() );
}

TEST( iscool_collections_sort_permutations, default_compare )
{
    const std::vector< int > values( { 9, 5, 8 } );

    const std::vector< std::size_t > indices
        ( iscool::collections::sort_permutation
          ( values.begin(), values.end() ) );

    EXPECT_EQ( values.size(), indices.size() );
    EXPECT_EQ( std::size_t( 1 ), indices[ 0 ] );
    EXPECT_EQ( std::size_t( 2 ), indices[ 1 ] );
    EXPECT_EQ( std::size_t( 0 ), indices[ 2 ] );
}

TEST( iscool_collections_sort_permutations, bounds )
{
    const std::vector< int > values( { 10, 9, 5, 8, 1 } );

    const std::vector< std::size_t > indices
        ( iscool::collections::sort_permutation
          ( values.begin() + 1, values.end() - 1 ) );

    EXPECT_EQ( values.size() - 2, indices.size() );
    EXPECT_EQ( std::size_t( 1 ), indices[ 0 ] );
    EXPECT_EQ( std::size_t( 2 ), indices[ 1 ] );
    EXPECT_EQ( std::size_t( 0 ), indices[ 2 ] );
}

TEST( iscool_collections_sort_permutations, custom_compare )
{
    const std::vector< int > values( { 9, 5, 8 } );

    const std::vector< std::size_t > indices
        ( iscool::collections::sort_permutation
          ( values.begin(), values.end(), std::greater< int >() ) );

    EXPECT_EQ( values.size(), indices.size() );
    EXPECT_EQ( std::size_t( 0 ), indices[ 0 ] );
    EXPECT_EQ( std::size_t( 2 ), indices[ 1 ] );
    EXPECT_EQ( std::size_t( 1 ), indices[ 2 ] );
}
