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
#include <iscool/signals/shared_connection.hpp>

iscool::signals::shared_connection::shared_connection()
  : _connection(nullptr)
{}

iscool::signals::shared_connection::shared_connection(const connection& c)
  : _connection(std::make_shared<scoped_connection>(c))
{}

iscool::signals::shared_connection::~shared_connection() = default;

bool iscool::signals::shared_connection::connected() const
{
  return (_connection != nullptr) && _connection->connected();
}

void iscool::signals::shared_connection::disconnect()
{
  if (_connection == nullptr)
    return;

  _connection->disconnect();
  _connection = nullptr;
}

bool iscool::signals::shared_connection::operator==(
    const shared_connection& that) const
{
  if ((_connection == nullptr) && (that._connection == nullptr))
    return true;

  if ((_connection == nullptr) || (that._connection == nullptr))
    return false;

  return *_connection == *that._connection;
}

bool iscool::signals::shared_connection::operator!=(
    const shared_connection& that) const
{
  return !(*this == that);
}
