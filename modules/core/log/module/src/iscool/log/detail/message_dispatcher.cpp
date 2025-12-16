// SPDX-License-Identifier: Apache-2.0
#include <iscool/log/detail/message_dispatcher.hpp>

#include <cassert>
#include <format>

iscool::log::detail::message_dispatcher::message_dispatcher()
  : _next_id(0)
  , _last_message_counter(0)
{}

std::size_t iscool::log::detail::message_dispatcher::register_delegates(
    const message_delegates& delegates)
{
  const std::unique_lock lock(_mutex);

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
  const std::unique_lock lock(_mutex);

  assert(_delegates.find(id) != _delegates.end());
  _delegates.erase(id);
}

void iscool::log::detail::message_dispatcher::clear()
{
  const std::unique_lock lock(_mutex);

  _delegates.clear();
}

void iscool::log::detail::message_dispatcher::dispatch_error(
    const context& context, const error::synopsis& synopsis)
{
  const std::unique_lock lock(_mutex);

  _last_message_counter = 0;

  for (const auto& e : _delegates)
    e.second.print_error(context, synopsis);
}

void iscool::log::detail::message_dispatcher::dispatch_to_delegates(
    const nature::nature& nature, const context& context,
    const std::string& message)
{
  if ((nature == _last_nature) && (context == _last_context)
      && (message == _last_message))
    {
      ++_last_message_counter;
      return;
    }

  if (_last_message_counter != 0)
    for (const auto& e : _delegates)
      e.second.print_message(_last_nature, _last_context,
                             std::format("Last message repeated {} time(s).",
                                         _last_message_counter));

  _last_message_counter = 0;
  _last_nature = nature;
  _last_context = context;
  _last_message = message;

  for (const auto& e : _delegates)
    e.second.print_message(nature, context, message);
}
