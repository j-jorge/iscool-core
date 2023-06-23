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
#include "iscool/net/message_deserializer.h"

#include "iscool/net/message_deserializer.impl.tpp"

iscool::net::message_deserializer::deserializer_collection::
    ~deserializer_collection()
{
  for (const auto& entry : _deserializers)
    delete entry.second;
}

void iscool::net::message_deserializer::deserializer_collection::dispatch(
    const endpoint& endpoint, const message& message) const
{
  typename deserializer_map::const_iterator it{ _deserializers.find(
      message.get_type()) };

  if (it != _deserializers.end())
    {
      assert(it->second != nullptr);
      it->second->dispatch(endpoint, message);
    }
}

iscool::net::message_deserializer::message_deserializer() = default;
iscool::net::message_deserializer::~message_deserializer() = default;

void iscool::net::message_deserializer::interpret_received_message(
    const endpoint& endpoint, const message& message) const
{
  _deserializers.dispatch(endpoint, message);
}
