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
#include <boost/range/algorithm/random_shuffle.hpp>

#include <boost/random/uniform_int_distribution.hpp>

#include <iterator>

template<typename T>
T iscool::random::rand::random( T min, T max )
{
    boost::random::uniform_int_distribution<T> rand( min, max );
    return rand( _generator );
} 

template<typename InputIterator>
InputIterator iscool::random::rand::random_in_sequence
( InputIterator first, InputIterator last )
{
    if ( first == last )
        return first;

    const std::size_t i
        ( random< std::size_t >( 0, std::distance( first, last ) - 1 ) );
    std::advance( first, i );
    
    return first;
}

template<typename randomIterator>
void iscool::random::rand::random_shuffle
( randomIterator first, randomIterator last )
{
    std::random_shuffle
        ( first, last,
          [this]( int max ) -> int { return random( 0, max - 1 ); } );
}
