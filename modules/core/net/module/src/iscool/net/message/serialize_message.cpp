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
#include "iscool/net/message/serialize_message.h"

#include "iscool/net/detail/apply_xor.h"
#include "iscool/net/message/message.h"

iscool::net::byte_array iscool::net::serialize_message(const message& m)
{
  return serialize_message(m, {});
}

iscool::net::byte_array iscool::net::serialize_message(const message& m,
                                                       const xor_key& key)
{
  return serialize_message(m, m.get_session_id(), m.get_channel_id(), key);
}

iscool::net::byte_array iscool::net::serialize_message(const message& m,
                                                       session_id session,
                                                       channel_id channel,
                                                       const xor_key& key)
{
  byte_array content(m.get_content());

  if (!key.empty())
    detail::apply_xor(content, key);

  const std::uint16_t size(sizeof(message_type) + sizeof(size)
                           + sizeof(session_id) + sizeof(channel_id)
                           + content.size());

  byte_array result;
  result.append(m.get_type());
  result.append(size);
  result.append(session);
  result.append(channel);
  result.append(content);

  return result;
}
