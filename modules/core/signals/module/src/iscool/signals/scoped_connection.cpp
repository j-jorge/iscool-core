// SPDX-License-Identifier: Apache-2.0
#include <iscool/signals/scoped_connection.hpp>

iscool::signals::scoped_connection::scoped_connection() = default;

iscool::signals::scoped_connection::scoped_connection(const connection& that)
  : _connection(that)
{}

iscool::signals::scoped_connection::scoped_connection(
    connection&& that) noexcept
  : _connection(std::move(that))
{}

iscool::signals::scoped_connection::scoped_connection(
    const scoped_connection& that)
  : _connection(that._connection)
{}

iscool::signals::scoped_connection::scoped_connection(
    scoped_connection&& that) noexcept
  : _connection(std::move(that._connection))
{}

iscool::signals::scoped_connection::~scoped_connection()
{
  _connection.disconnect();
}

bool iscool::signals::scoped_connection::operator==(
    const scoped_connection& that) const
{
  return that._connection == _connection;
}

bool iscool::signals::scoped_connection::operator!=(
    const scoped_connection& that) const
{
  return !(*this == that);
}

bool iscool::signals::scoped_connection::operator==(
    const connection& that) const
{
  return that == _connection;
}

bool iscool::signals::scoped_connection::operator!=(
    const connection& that) const
{
  return !(*this == that);
}

iscool::signals::scoped_connection&
iscool::signals::scoped_connection::operator=(const connection& that)
{
  if (_connection == that)
    return *this;

  disconnect();
  _connection = that;

  return *this;
}

iscool::signals::scoped_connection&
iscool::signals::scoped_connection::operator=(connection&& that) noexcept
{
  if (_connection == that)
    return *this;

  disconnect();
  _connection = std::move(that);

  return *this;
}

iscool::signals::scoped_connection&
iscool::signals::scoped_connection::operator=(const scoped_connection& that)
{
  if (this == &that)
    return *this;

  disconnect();
  _connection = that._connection;

  return *this;
}

iscool::signals::scoped_connection&
iscool::signals::scoped_connection::operator=(
    scoped_connection&& that) noexcept
{
  if (this == &that)
    return *this;

  disconnect();
  _connection = std::move(that._connection);

  return *this;
}

void iscool::signals::scoped_connection::disconnect() const
{
  _connection.disconnect();
}

bool iscool::signals::scoped_connection::connected() const
{
  return _connection.connected();
}
