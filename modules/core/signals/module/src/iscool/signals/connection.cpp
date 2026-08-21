// SPDX-License-Identifier: Apache-2.0
#include <iscool/signals/connection.hpp>

#include <iscool/signals/detail/slot.hpp>

iscool::signals::connection::connection() = default;

iscool::signals::connection::connection(
    const std::weak_ptr<detail::slot>& slot)
  : _slot(slot)
{}

iscool::signals::connection::connection(const connection& that)
  : _slot(that._slot)
{}

iscool::signals::connection::connection(connection&& that) noexcept
  : _slot(std::move(that._slot))
{}

iscool::signals::connection::~connection() = default;

iscool::signals::connection&
iscool::signals::connection::operator=(const connection& that)
{
  _slot = that._slot;
  return *this;
}

iscool::signals::connection&
iscool::signals::connection::operator=(connection&& that) noexcept
{
  _slot = std::move(that._slot);
  return *this;
}

bool iscool::signals::connection::operator==(const connection& that) const
{
  static const std::owner_less<decltype(_slot)> comparator{};

  return !(comparator(_slot, that._slot) || comparator(that._slot, _slot));
}

bool iscool::signals::connection::operator!=(const connection& that) const
{
  return !(*this == that);
}

bool iscool::signals::connection::connected() const
{
  const std::shared_ptr<detail::slot> s(_slot.lock());
  return (s != nullptr) && s->connected();
}

void iscool::signals::connection::disconnect() const
{
  const std::shared_ptr<detail::slot> s(_slot.lock());

  if (s != nullptr)
    s->disconnect();
}
