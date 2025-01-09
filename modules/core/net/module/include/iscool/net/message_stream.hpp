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
#pragma once

#include <iscool/net/endpoint.hpp>
#include <iscool/net/message/channel_id.hpp>
#include <iscool/net/message/session_id.hpp>
#include <iscool/net/message_pool.hpp>
#include <iscool/net/xor_key.hpp>

#include <iscool/signals/declare_signal.hpp>
#include <iscool/signals/scoped_connection.hpp>

namespace iscool::net
{
  class byte_array;
  class message;
  class socket_stream;

  class message_stream
  {
  public:
    DECLARE_SIGNAL(void(const endpoint&, const iscool::net::message&), message,
                   _message);

  public:
    explicit message_stream(socket_stream& socket);
    message_stream(socket_stream& socket, xor_key key);
    ~message_stream();

    void send(const iscool::net::message& message) const;
    void send(const iscool::net::message& message, session_id session,
              channel_id channel) const;

    void send(const endpoint& target,
              const iscool::net::message& message) const;
    void send(const endpoint& target, const iscool::net::message& message,
              session_id session, channel_id channel) const;

  private:
    void dispatch_message(const endpoint& endpoint, const byte_array& bytes);

  private:
    socket_stream& _socket;
    const xor_key _key;
    iscool::signals::scoped_connection _socket_connection;
    message_pool _message_pool;
  };
}
