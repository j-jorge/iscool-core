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
#include <iscool/net/message/deserialize_message.hpp>

#include <iscool/net/byte_array_reader.hpp>
#include <iscool/net/detail/apply_xor.hpp>

#include <cassert>

iscool::net::message iscool::net::deserialize_message(const byte_array& bytes)
{
  return deserialize_message(bytes, {});
}

iscool::net::message iscool::net::deserialize_message(const byte_array& bytes,
                                                      const xor_key& key)
{
  byte_array_reader reader(bytes);

  const message_type type(reader.get<message_type>());

  const std::uint16_t size(reader.get<std::uint16_t>());
  assert(bytes.size() == size);
  (void)size;

  const session_id session(reader.get<session_id>());
  const channel_id channel(reader.get<channel_id>());

  byte_array content(reader.slice());

  if (!key.empty())
    detail::apply_xor(content, key);

  return message(type, session, channel, content);
}
