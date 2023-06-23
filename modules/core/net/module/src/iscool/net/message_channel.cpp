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
#include <iscool/net/message_channel.hpp>

#include <iscool/net/message/message.hpp>
#include <iscool/net/message_stream.hpp>
#include <iscool/signals/implement_signal.hpp>

IMPLEMENT_SIGNAL(iscool::net::message_channel, message, _message);

iscool::net::message_channel::message_channel(const message_stream& stream,
                                              session_id session_id,
                                              channel_id channel_id)
  : _session_id(session_id)
  , _channel_id(channel_id)
  , _stream(stream)
  , _received_signal_connection(_stream.connect_to_message(
        std::bind(&message_channel::process_incoming_message, this,
                  std::placeholders::_1, std::placeholders::_2)))
{}

iscool::net::message_channel::~message_channel() = default;

void iscool::net::message_channel::send(const message& message) const
{
  _stream.send(message, _session_id, _channel_id);
}

void iscool::net::message_channel::send(const endpoint& endpoint,
                                        const message& message) const
{
  _stream.send(endpoint, message, _session_id, _channel_id);
}

void iscool::net::message_channel::process_incoming_message(
    const endpoint& endpoint, const message& message) const
{
  if ((message.get_session_id() != _session_id)
      || (message.get_channel_id() != _channel_id))
    return;

  _message(endpoint, message);
}
