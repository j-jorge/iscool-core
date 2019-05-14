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
#ifndef ISCOOL_COLLECTIONS_RANK_TPP
#define ISCOOL_COLLECTIONS_RANK_TPP

template< typename Iterator, typename Output >
void iscool::collections::rank
( Iterator value_first, Iterator value_last, Output&& output )
{
    if ( value_first == value_last )
        return;
    
    Iterator reference_value( value_first );
    std::size_t rank( 1 );
    std::size_t count( 0 );
    output( rank );

    for ( ++value_first, ++count;
          value_first != value_last;
          ++value_first, ++count )
    {
        if ( *value_first != *reference_value )
        {
            rank = count + 1;
            reference_value = value_first;
        }

        output( rank );
    }
}

template
<
    typename ValueIterator,
    typename OrderIterator,
    typename Output
>
void iscool::collections::rank
( ValueIterator values, OrderIterator order_first,
  OrderIterator order_last, Output&& output )
{
    if ( order_first == order_last )
        return;

    auto index( *order_first );
    ValueIterator reference_value( values + index );
    std::size_t rank( 1 );
    std::size_t count( 0 );
    output( rank );

    for ( ++order_first, ++count;
          order_first != order_last;
          ++order_first, ++count )
    {
        index = *order_first;
        ValueIterator value( values + index );
        
        if ( *value != *reference_value )
        {
            rank = count + 1;
            reference_value = value;
        }

        output( rank );
    }
}

#endif
