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
#include "iscool/iterators/back_emplace_iterator.h"

#include <deque>
#include <list>
#include <vector>

#include <gtest/gtest.h>

namespace iscool
{
    namespace iterators
    {
        namespace test
        {
            template< template< typename... > class Container >
            void back_emplace_iterator_assignment();
            template< template< typename... > class Container >
            void back_emplace_iterator_copy();
            template< template< typename... > class Container >
            void back_emplace_iterator_operators();
        }
    }
}

template< template< typename... > class Container >
void iscool::iterators::test::back_emplace_iterator_assignment()
{
    Container< int > result;

    iscool::iterators::back_emplace_iterator< Container< int > > it( result );

    *it = 3;
    *it = 2;
    *it = 1;

    const Container< int > expected( { 3, 2, 1 } );
    EXPECT_EQ( expected, result );
    
}
    
template< template< typename... > class Container >
void iscool::iterators::test::back_emplace_iterator_copy()
{
    Container< int > result;
    const Container< int > source( { 2, 1, 3 } );

    std::copy
        ( source.begin(), source.end(),
          iscool::iterators::back_emplacer( result ) );

    EXPECT_EQ( source, result );
}

template< template< typename... > class Container >
void iscool::iterators::test::back_emplace_iterator_operators()
{
    Container< std::string > result;

    auto it( iscool::iterators::back_emplacer( result ) );
    auto copy( it++ );

    *it = "a";
    *copy = "b";

    std::string moved( "c" );
    *it = std::move( moved );

    const Container< std::string > expected( { "a", "b", "c" } );
    
    EXPECT_EQ( expected, result );
    EXPECT_TRUE( moved.empty() );
}

TEST( iscool_iterators_back_emplace_iterator_test, assignment_vector )
{
    iscool::iterators::test::back_emplace_iterator_assignment< std::vector >();
}

TEST( iscool_iterators_back_emplace_iterator_test, assignment_deque )
{
    iscool::iterators::test::back_emplace_iterator_assignment< std::deque >();
}

TEST( iscool_iterators_back_emplace_iterator_test, assignment_list )
{
    iscool::iterators::test::back_emplace_iterator_assignment< std::list >();
}

TEST( iscool_iterators_back_emplace_iterator_test, copy_vector )
{
    iscool::iterators::test::back_emplace_iterator_copy< std::vector >();
}

TEST( iscool_iterators_back_emplace_iterator_test, copy_deque )
{
    iscool::iterators::test::back_emplace_iterator_copy< std::deque >();
}

TEST( iscool_iterators_back_emplace_iterator_test, copy_list )
{
    iscool::iterators::test::back_emplace_iterator_copy< std::list >();
}

TEST( iscool_iterators_back_emplace_iterator_test, operators_vector )
{
    iscool::iterators::test::back_emplace_iterator_operators< std::vector >();
}

TEST( iscool_iterators_back_emplace_iterator_test, operators_deque )
{
    iscool::iterators::test::back_emplace_iterator_operators< std::deque >();
}

TEST( iscool_iterators_back_emplace_iterator_test, operators_list )
{
    iscool::iterators::test::back_emplace_iterator_operators< std::list >();
}
