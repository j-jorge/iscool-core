// SPDX-License-Identifier: Apache-2.0
#include <iscool/schedule/scoped_connection.hpp>

iscool::schedule::scoped_connection::scoped_connection() = default;

iscool::schedule::scoped_connection::scoped_connection(connection c)
  : _connection(std::move(c))
{}

iscool::schedule::scoped_connection::scoped_connection(
    scoped_connection&& that)
  : _connection(std::move(that._connection))
{
  that._connection = {};
}

iscool::schedule::scoped_connection::~scoped_connection()
{
  _connection.disconnect();
}

iscool::schedule::scoped_connection&
iscool::schedule::scoped_connection::operator=(scoped_connection&& that)
{
  if (this == &that)
    return *this;

  _connection.disconnect();
  _connection = that._connection;
  that._connection = {};

  return *this;
}

iscool::schedule::scoped_connection&
iscool::schedule::scoped_connection::operator=(const connection& c)
{
  _connection.disconnect();
  _connection = c;

  return *this;
}

bool iscool::schedule::scoped_connection::connected() const
{
  return _connection.connected();
}

void iscool::schedule::scoped_connection::disconnect()
{
  _connection.disconnect();
}
