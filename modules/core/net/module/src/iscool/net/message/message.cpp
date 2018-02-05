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
#include "iscool/net/message/message.h"

iscool::net::message::message() = default;

iscool::net::message::message( message_type type, const byte_array& content )
    : message( type, 0, 0, content )
{

}

iscool::net::message::message
( message_type type, session_id session, channel_id channel,
  const byte_array& content )
    : _type( type ),
      _session_id( session ),
      _channel_id( channel ),
      _content( content )
{

}

void iscool::net::message::set_session_id( session_id session_id )
{
    _session_id = session_id;
}

iscool::net::session_id iscool::net::message::get_session_id() const
{
    return _session_id;
}

void iscool::net::message::set_channel_id( channel_id channel_id )
{
    _channel_id = channel_id;
}

iscool::net::channel_id iscool::net::message::get_channel_id() const
{
    return _channel_id;
}

iscool::net::message_type iscool::net::message::get_type() const
{
    return _type;
}

const iscool::net::byte_array& iscool::net::message::get_content() const
{
    return _content;
}
