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
#include <iscool/log/detail/message_dispatcher.hpp>

#include <cassert>

iscool::log::detail::message_dispatcher::message_dispatcher()
  : _next_id(0)
{}

std::size_t iscool::log::detail::message_dispatcher::register_delegates(
    const message_delegates& delegates)
{
  assert(delegates.is_valid());
  assert(_delegates.find(_next_id) == _delegates.end());

  const std::size_t result(_next_id);
  ++_next_id;
  _delegates[result] = delegates;

  return result;
}

void iscool::log::detail::message_dispatcher::unregister_delegates(
    std::size_t id)
{
  assert(_delegates.find(id) != _delegates.end());
  _delegates.erase(id);
}

void iscool::log::detail::message_dispatcher::clear()
{
  _delegates.clear();
}

void iscool::log::detail::message_dispatcher::dispatch_error(
    const context& context, const error::synopsis& synopsis) const
{
  for (const auto& e : _delegates)
    e.second.print_error(context, synopsis);
}

void iscool::log::detail::message_dispatcher::dispatch_to_delegates(
    const nature::nature& nature, const context& context,
    const std::string& message) const
{
  for (const auto& e : _delegates)
    e.second.print_message(nature, context, message);
}
