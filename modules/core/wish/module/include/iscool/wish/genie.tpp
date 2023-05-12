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
#ifndef GENIE_TPP
#define GENIE_TPP

#include <cassert>

template<typename T>
void iscool::wish::genie::empower( std::function<void( const T& )> function )
{
    const auto insertion
        ( _powers.insert
          ( std::make_pair( T::kind(), function ) ) );
    (void) insertion;
    assert( insertion.second );
}

template< typename T>
void iscool::wish::genie::deny()
{
    const power_list::const_iterator iterator
        ( _powers.find( T::kind() ) );
    assert( iterator != _powers.end() );

    _powers.erase( iterator );
}

template< typename T >
void iscool::wish::genie::grant( const T& wish ) const
{
    const power_list::const_iterator iterator
        ( _powers.find( T::kind() ) );
    assert( iterator != _powers.end() );

    return boost::any_cast
        <std::function<void( const T& )>>( iterator->second )( wish );
}

template< typename T >
bool iscool::wish::genie::is_wish_valid() const
{
    return _powers.find( T::kind() ) != _powers.end();
}

#endif
