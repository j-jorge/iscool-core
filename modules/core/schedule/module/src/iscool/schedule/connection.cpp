// SPDX-License-Identifier: Apache-2.0
#include <iscool/schedule/connection.hpp>

#include <iscool/schedule/detail/call_later.hpp>

iscool::schedule::connection::connection() = default;

iscool::schedule::connection::connection(iscool::signals::connection c)
  : _signal_connection(std::move(c))
{}

bool iscool::schedule::connection::connected() const
{
  return detail::call_manager.connected(*this);
}

void iscool::schedule::connection::disconnect()
{
  detail::call_manager.disconnect(*this);
}
