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
#include "iscool/net/message_channel.h"

#include "iscool/net/byte_array.h"
#include "iscool/net/byte_array_reader.h"
#include "iscool/net/message/deserialize_message.h"
#include "iscool/net/message/message.h"
#include "iscool/net/message/serialize_message.h"
#include "iscool/net/socket_stream.h"
#include "iscool/signals/implement_signal.h"

#include <boost/bind.hpp>

IMPLEMENT_SIGNAL( iscool::net::message_channel, message, _message );

iscool::net::message_channel::message_channel
( socket_stream& socket, session_id session_id, channel_id channel_id,
  const xor_key& key )
    : _session_id( session_id ),
      _channel_id( channel_id ),
      _xor_key( key ),
      _socket( socket ),
      _received_signal_connection( create_signal_connection() )
{

}

iscool::net::message_channel::message_channel( const message_channel& that )
    : _session_id( that._session_id ),
      _channel_id( that._channel_id ),
      _xor_key( that._xor_key ),
      _socket( that._socket ),
      _received_signal_connection( create_signal_connection() )
{

}

iscool::net::message_channel::~message_channel()
{
    _received_signal_connection.disconnect();
}

iscool::net::socket_stream& iscool::net::message_channel::get_socket() const
{
    return _socket;
}

iscool::net::session_id iscool::net::message_channel::get_session_id() const
{
    return _session_id;
}

iscool::net::channel_id iscool::net::message_channel::get_channel_id() const
{
    return _channel_id;
}

const iscool::net::xor_key&
iscool::net::message_channel::get_obfuscation_key() const
{
    return _xor_key;
}

void iscool::net::message_channel::send( const message& message ) const
{
    _socket.send
        ( serialize_message( message, _session_id, _channel_id, _xor_key ) );
}

void iscool::net::message_channel::send
( const endpoint& endpoint, const message& message ) const
{
    _socket.send
        ( endpoint,
          serialize_message( message, _session_id, _channel_id, _xor_key ) );
}

iscool::signals::connection
iscool::net::message_channel::create_signal_connection() const
{
    return _socket.connect_to_received
        ( boost::bind
          ( &message_channel::process_incoming_bytes, this, _1, _2 ) );
}

void
iscool::net::message_channel::process_incoming_bytes
( const endpoint& endpoint, const byte_array& bytes ) const
{
    const message result( deserialize_message( bytes, _xor_key ) );

    if ( ( result.get_session_id() != _session_id )
         || ( result.get_channel_id() != _channel_id ) )
        return;
    
    _message( endpoint, result );
}
