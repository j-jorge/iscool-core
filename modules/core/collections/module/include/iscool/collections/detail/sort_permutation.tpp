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
#ifndef ISCOOL_COLLECTIONS_SORT_PERMUTATION_TPP
#define ISCOOL_COLLECTIONS_SORT_PERMUTATION_TPP

#include <algorithm>
#include <iterator>
#include <numeric>

namespace iscool
{
    namespace collections
    {
        namespace detail
        {
            template< bool Booleans >
            struct sort_helper;

            template<>
            struct sort_helper< true >
            {
                template< typename Iterator, typename Compare >
                static std::vector< std::size_t > permutation
                ( const Iterator& first, const Iterator& last,
                  const Compare& compare );
            };

            template<>
            struct sort_helper< false >
            {
                template< typename Iterator, typename Compare >
                static std::vector< std::size_t > permutation
                ( const Iterator& first, const Iterator& last,
                  const Compare& compare );
            };
        }
    }
}

template< typename Iterator >
std::vector< std::size_t > iscool::collections::sort_permutation
( const Iterator& first, const Iterator& last )
{
    return sort_permutation
        ( first, last,
          std::less
          <
              typename std::iterator_traits< Iterator >::value_type
          >() );
}

template< typename Iterator, typename Compare >
std::vector< std::size_t > iscool::collections::sort_permutation
( const Iterator& first, const Iterator& last, const Compare& compare )
{
    return detail::sort_helper
        <
            std::is_same
            <
                typename std::iterator_traits< Iterator >::value_type,
                bool
            >::value
        >::permutation( first, last, compare );
}

template< typename Iterator, typename Compare >
std::vector< std::size_t >
iscool::collections::detail::sort_helper< true >::permutation
( const Iterator& first, const Iterator& last, const Compare& compare )
{
    const std::size_t count( last - first );
    std::size_t out_first( 0 );
    std::size_t out_last( count );
    std::vector< std::size_t > result( count );

    Iterator it( first );
    
    for ( std::size_t i( 0 ); i != count; ++i, ++it )
        if ( compare( *it, true ) )
        {
            result[ out_first ] = i;
            ++out_first;
        }
        else
        {
            --out_last;
            result[ out_last ] = i;
        }

    return result;
}

template< typename Iterator, typename Compare >
std::vector< std::size_t >
iscool::collections::detail::sort_helper< false >::permutation
( const Iterator& first, const Iterator& last, const Compare& compare )
{
    std::vector< std::size_t > result( last - first );

    const auto bit( result.begin() );
    const auto eit( result.end() );
    
    std::iota( bit, eit, 0 );

    const auto predicate
        ( [ &first, &compare ]( std::size_t i, std::size_t j ) -> bool
          {
              return compare( *( first + i ), *( first + j ) );
          } );

    std::sort( bit, eit, predicate );
    
    return result;
}

#endif
