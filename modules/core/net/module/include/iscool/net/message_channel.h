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
#ifndef ISCOOL_NET_MESSAGE_CHANNEL_H
#define ISCOOL_NET_MESSAGE_CHANNEL_H

#include "iscool/net/endpoint.h"
#include "iscool/net/xor_key.h"
#include "iscool/net/message/channel_id.h"
#include "iscool/net/message/session_id.h"

#include "iscool/signals/declare_signal.h"

namespace iscool
{
    namespace net
    {
        class byte_array;
        class message;
        class socket_stream;
                
        class message_channel
        {
        public:
            DECLARE_SIGNAL
            ( void( const endpoint&, const message& ), message, _message );
            
        public:
            message_channel
            ( socket_stream& socket, session_id session_id,
              channel_id channel_id, const xor_key& key );
            message_channel( const message_channel& that );
            ~message_channel();

            socket_stream& get_socket() const;
            session_id get_session_id() const;
            channel_id get_channel_id() const;
            const xor_key& get_obfuscation_key() const;

            void send( const message& message ) const;
            void send
            ( const endpoint& endpoint, const message& message ) const;

        private:
            iscool::signals::connection create_signal_connection() const;

            void
            process_incoming_bytes
            ( const endpoint& endpoint, const byte_array& bytes ) const;

        private:
            const session_id _session_id;
            const channel_id _channel_id;
            const xor_key _xor_key;
            socket_stream& _socket;
            const iscool::signals::connection _received_signal_connection;
        };
    }
}

#endif
