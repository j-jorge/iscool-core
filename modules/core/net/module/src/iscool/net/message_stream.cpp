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
#include <iscool/net/message_stream.hpp>

#include <iscool/net/message/deserialize_message.hpp>
#include <iscool/net/message/message.hpp>
#include <iscool/net/message/serialize_message.hpp>
#include <iscool/net/socket_stream.hpp>
#include <iscool/signals/implement_signal.hpp>

IMPLEMENT_SIGNAL(iscool::net::message_stream, message, _message);

iscool::net::message_stream::message_stream(iscool::net::socket_stream& socket)
  : message_stream(socket, xor_key{})
{}

iscool::net::message_stream::message_stream(iscool::net::socket_stream& socket,
                                            xor_key key)
  : _socket(socket)
  , _key(std::move(key))
  , _socket_connection(socket.connect_to_received(
        std::bind(&message_stream::dispatch_message, this,
                  std::placeholders::_1, std::placeholders::_2)))
{}

iscool::net::message_stream::~message_stream() = default;

void iscool::net::message_stream::send(
    const iscool::net::message& message) const
{
  _socket.send(serialize_message(message, _key));
}

void iscool::net::message_stream::send(const iscool::net::message& message,
                                       session_id session,
                                       channel_id channel) const
{
  _socket.send(serialize_message(message, session, channel, _key));
}

void iscool::net::message_stream::send(
    const endpoint& target, const iscool::net::message& message) const
{
  _socket.send(target, serialize_message(message, _key));
}

void iscool::net::message_stream::send(const endpoint& target,
                                       const iscool::net::message& message,
                                       session_id session,
                                       channel_id channel) const
{
  _socket.send(target, serialize_message(message, session, channel, _key));
}

void iscool::net::message_stream::dispatch_message(
    const iscool::net::endpoint& target, const byte_array& bytes) const
{
  message m;

  try
    {
      m = deserialize_message(bytes, _key);
    }
  catch (const std::out_of_range&)
    {
      return;
    }

  _message(target, m);
}
