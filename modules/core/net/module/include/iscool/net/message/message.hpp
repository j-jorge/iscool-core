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
#ifndef ISCOOL_NET_MESSAGE_H
#define ISCOOL_NET_MESSAGE_H

#include <iscool/net/byte_array.hpp>
#include <iscool/net/message/channel_id.hpp>
#include <iscool/net/message/message_type.hpp>
#include <iscool/net/message/session_id.hpp>

namespace iscool
{
  namespace net
  {
    class message
    {
    public:
      message();
      message(message_type type, const byte_array& content);
      message(message_type type, session_id session, channel_id channel,
              const byte_array& content);

      void set_session_id(session_id session_id);
      session_id get_session_id() const;

      void set_channel_id(channel_id channel_id);
      channel_id get_channel_id() const;

      message_type get_type() const;
      const byte_array& get_content() const;

    private:
      message_type _type;
      session_id _session_id;
      channel_id _channel_id;
      byte_array _content;
    };
  }
}

#endif
