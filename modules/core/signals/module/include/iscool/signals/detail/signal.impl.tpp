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
#ifndef ISCOOL_SIGNALS_DETAIL_SIGNAL_IMPL_TPP
#define ISCOOL_SIGNALS_DETAIL_SIGNAL_IMPL_TPP

template< typename Signature >
iscool::signals::detail::signal< Signature >::signal() = default;

template< typename Signature >
iscool::signals::detail::signal< Signature >::~signal() = default;

template< typename Signature >
iscool::signals::connection
iscool::signals::detail::signal< Signature >::connect
( const boost::function< Signature >& f )
{
    _slots.emplace_back( std::make_shared< internal_slot >( f ) );
    return connection( _slots.back() );
}

template< typename Signature >
template< typename... Arg >
void
iscool::signals::detail::signal< Signature >::operator()( Arg&&... arg ) const
{
    std::vector< std::shared_ptr< slot > > slots( _slots );

    for( const auto& s : slots )
        if ( s->connected() )
            std::dynamic_pointer_cast< internal_slot >( s )->callback
                ( std::forward< Arg >( arg )... );
}

template< typename Signature >
bool iscool::signals::detail::signal< Signature >::empty() const
{
    for ( const auto& s : _slots )
        if ( s->connected() )
            return false;

    return true;
}

template< typename Signature >
void iscool::signals::detail::signal< Signature >::disconnect_all_slots()
{
    _slots.clear();
}

template< typename Signature >
std::size_t iscool::signals::detail::signal< Signature >::num_slots() const
{
    std::size_t result( 0 );

    for ( const auto& s : _slots )
        if ( s->connected() )
            ++result;

    return result;
}

template< typename Signature >
void iscool::signals::detail::signal< Signature >::swap
( signal< Signature >& that )
{
    _slots.swap( that._slots );
}
    
template< typename Signature >
iscool::signals::detail::signal< Signature >::internal_slot::internal_slot
( const boost::function< Signature >& f )
    : callback( f )
{

}

template< typename Signature >
iscool::signals::detail::signal< Signature >::internal_slot::~internal_slot() =
    default;

#endif
