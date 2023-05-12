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
#ifndef ISCOOL_NET_MESSAGE_DESERIALIZER_IMPL_TPP
#define ISCOOL_NET_MESSAGE_DESERIALIZER_IMPL_TPP

#include "iscool/net/message/message.h"
#include "iscool/signals/declare_signal.h"
#include "iscool/signals/implement_signal.h"

#include <boost/bind.hpp>

class iscool::net::message_deserializer::deserializer_base
{
public:
    virtual ~deserializer_base() = default;
    virtual void dispatch
    ( const endpoint& endpoint, const message& message ) const = 0;
};

template< typename M >
class iscool::net::message_deserializer::typed_deserializer:
    public deserializer_base
{
    DECLARE_SIGNAL_IN_TEMPLATE
    ( void ( const endpoint&, const M& ), message, _message );

public:
    void dispatch
    ( const endpoint& endpoint, const message& message ) const override;
};

template< typename M >
void iscool::net::message_deserializer::typed_deserializer< M >::dispatch
( const endpoint& endpoint, const message& message ) const
{
    assert( message.get_type() == M::get_type() );
    _message( endpoint, M( message.get_content() ) );
}

template< typename M >
IMPLEMENT_SIGNAL
( iscool::net::message_deserializer::typed_deserializer< M >, message,
  _message );

template< typename M >
iscool::signals::connection
iscool::net::message_deserializer::deserializer_collection::connect
( const std::function< void ( const endpoint&, const M& ) >& f )
{
    typed_deserializer< M >* deserializer;

    const message_type message_type( M::get_type() );

    typename deserializer_map::iterator it
        (  _deserializers.find( message_type ) );

    if ( it == _deserializers.end() )
    {
        deserializer = new typed_deserializer< M >();
        _deserializers[ message_type ] = deserializer;
    }
    else
        deserializer = dynamic_cast< typed_deserializer< M >* >( it->second );

    assert( deserializer != nullptr );
    assert( _deserializers.find( message_type ) != _deserializers.end() );

    return deserializer->connect_to_message( f );
}

template< typename M >
iscool::signals::connection
iscool::net::message_deserializer::connect_signal
( const std::function< void ( const endpoint&, M ) >& f )
{
    return _deserializers.connect< M >( f );
}

#endif
