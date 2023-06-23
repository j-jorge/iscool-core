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
#include "iscool/signals/signal.h"

#include "iscool/signals/scoped_connection.h"
#include "iscool/signals/signal.impl.tpp"

#include <gtest/gtest.h>

TEST(iscool_signals_scoped_connection, initially_disconnected)
{
  iscool::signals::scoped_connection connection;
  EXPECT_FALSE(connection.connected());
}

TEST(iscool_signals_scoped_connection, connected)
{
  iscool::signals::signal<void()> signal;

  iscool::signals::scoped_connection connection(signal.connect(
      []() -> void
      {
      }));

  EXPECT_TRUE(connection.connected());
}

TEST(iscool_signals_scoped_connection, disconnect)
{
  iscool::signals::signal<void()> signal;

  bool called(false);

  iscool::signals::scoped_connection connection(signal.connect(
      [&called]() -> void
      {
        called = true;
      }));

  connection.disconnect();
  EXPECT_FALSE(connection.connected());

  signal();
  EXPECT_FALSE(called);
}

TEST(iscool_signals_scoped_connection, disconnect_when_leave_scope)
{
  iscool::signals::signal<void()> signal;

  iscool::signals::connection connection(signal.connect(
      []() -> void
      {
      }));

  {
    iscool::signals::scoped_connection scoped(connection);
  }

  EXPECT_FALSE(connection.connected());
}

TEST(iscool_signals_scoped_connection, no_disconnect_if_moved)
{
  iscool::signals::signal<void()> signal;

  bool called(false);

  iscool::signals::scoped_connection connection;

  {
    iscool::signals::scoped_connection c(signal.connect(
        [&called]() -> void
        {
          called = true;
        }));

    connection = std::move(c);
  }

  signal();
  EXPECT_TRUE(called);
}
