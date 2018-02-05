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
#ifndef ISCOOL_COLLECTIONS_BINARY_SEARCH_TPP
#define ISCOOL_COLLECTIONS_BINARY_SEARCH_TPP

template< typename Iterator, typename Criterion >
Iterator iscool::collections::binary_search
( const Iterator& first, const Iterator& last, const Criterion& criterion )
{
    int count( last - first );
    Iterator range_begin( first );

    while ( count > 0 )
    {
        const int step( count / 2 );
        const Iterator it( range_begin + step ); 
        const auto diff( criterion( *it ) );

        if ( diff == 0 )
            return it;

        if ( diff < 0 )
        {
            range_begin = it + 1; 
            count -= step + 1; 
        }
        else
            count = step;
    }
    
    return last;
}

#endif
