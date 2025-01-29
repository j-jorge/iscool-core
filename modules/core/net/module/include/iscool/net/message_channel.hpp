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

#include <iscool/net/endpoint.hpp>
#include <iscool/net/message/channel_id.hpp>
#include <iscool/net/message/session_id.hpp>

#include <iscool/signals/declare_signal.hpp>
#include <iscool/signals/scoped_connection.hpp>

namespace iscool
{
  namespace net
  {
    class byte_array;
    class message;
    class message_stream;

    class message_channel
    {
    public:
      DECLARE_SIGNAL(void(const endpoint&, const message&), message, _message)

    public:
      message_channel(const message_stream& stream);
      message_channel(const message_stream& stream, session_id session_id,
                      channel_id channel_id);
      ~message_channel();

      void rebind(session_id session_id, channel_id channel_id);

      void send(const message& message) const;
      void send(const endpoint& endpoint, const message& message) const;

    private:
      void process_incoming_message(const endpoint& endpoint,
                                    const message& message) const;

    private:
      session_id _session_id;
      channel_id _channel_id;
      const message_stream& _stream;

      iscool::signals::scoped_connection _received_signal_connection;
    };
  }
}

#endif
