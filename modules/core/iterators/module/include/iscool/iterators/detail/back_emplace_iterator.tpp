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
#ifndef ISCOOL_ITERATORS_BACK_EMPLACE_ITERATOR_TPP
#define ISCOOL_ITERATORS_BACK_EMPLACE_ITERATOR_TPP

template< typename Container >
iscool::iterators::back_emplace_iterator< Container >::back_emplace_iterator
( Container& container )
    : _container( &container )
{

}

template< typename Container >
iscool::iterators::back_emplace_iterator< Container >&
iscool::iterators::back_emplace_iterator< Container >::operator=
( const typename Container::value_type& value )
{
    _container->emplace_back( value );
    return *this;
}

template< typename Container >
iscool::iterators::back_emplace_iterator< Container >&
iscool::iterators::back_emplace_iterator< Container >::operator=
( typename Container::value_type&& value )
{
    _container->emplace_back( std::move( value ) );
    return *this;
}

template< typename Container >
iscool::iterators::back_emplace_iterator< Container >&
iscool::iterators::back_emplace_iterator< Container >::operator++()
{
    return *this;
}

template< typename Container >
iscool::iterators::back_emplace_iterator< Container >
iscool::iterators::back_emplace_iterator< Container >::operator++( int )
{
    return *this;
}

template< typename Container >
iscool::iterators::back_emplace_iterator< Container >&
iscool::iterators::back_emplace_iterator< Container >::operator*()
{
    return *this;
}

template< typename Container >
iscool::iterators::back_emplace_iterator< Container >
iscool::iterators::back_emplacer( Container& container )
{
    return back_emplace_iterator< Container >( container );
}

#endif
