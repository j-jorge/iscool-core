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
#include <iscool/schedule/delayed_call.hpp>
#include <iscool/schedule/manual_scheduler.hpp>
#include <iscool/schedule/setup.hpp>

#include <iscool/optional.hpp>

#include <thread>
#include <unistd.h>

#include "gtest/gtest.h"

TEST(iscool_schedule_delayed_call, default_delay)
{
  iscool::optional<std::chrono::nanoseconds> scheduled_delay;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        scheduled_delay = delay;
      });

  iscool::schedule::initialize(delegate);
  iscool::schedule::delayed_call(
      []() -> void
      {
      });

  EXPECT_TRUE(!!scheduled_delay);
  EXPECT_EQ(0, scheduled_delay->count());

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, delay_cast)
{
  iscool::optional<std::chrono::nanoseconds> scheduled_delay;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        scheduled_delay = delay;
      });

  iscool::schedule::initialize(delegate);
  iscool::schedule::delayed_call(
      []() -> void
      {
      },
      std::chrono::seconds(2));

  EXPECT_TRUE(!!scheduled_delay);
  EXPECT_EQ(2'000'000'000, scheduled_delay->count());

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, call)
{
  iscool::signals::void_signal_function callback;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        callback = f;
      });

  iscool::schedule::initialize(delegate);

  bool called(false);
  const auto f(
      [&called]() -> void
      {
        called = true;
      });
  iscool::schedule::delayed_call(f);

  EXPECT_TRUE(callback);

  callback();

  EXPECT_TRUE(called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, connection)
{
  iscool::signals::void_signal_function callback;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        callback = f;
      });

  iscool::schedule::initialize(delegate);

  bool called(false);
  const auto f(
      [&called]() -> void
      {
        called = true;
      });
  iscool::schedule::delayed_call(f).disconnect();
  callback();

  EXPECT_FALSE(called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, disconnect_in_callback)
{
  std::vector<iscool::signals::void_signal_function> calls;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        calls.push_back(f);
      });

  iscool::schedule::initialize(delegate);

  bool second_call_called(false);
  auto second_call(
      [&second_call_called]() -> void
      {
        second_call_called = true;
      });

  iscool::signals::connection second_call_connection;
  auto first_call(
      [&second_call_connection]() -> void
      {
        second_call_connection.disconnect();
      });

  iscool::schedule::delayed_call(first_call);
  second_call_connection = iscool::schedule::delayed_call(second_call);

  EXPECT_FALSE(calls.empty());
  calls[0]();
  EXPECT_FALSE(second_call_called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, short_call_cumulated)
{
  std::vector<iscool::signals::void_signal_function> calls;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        calls.push_back(f);
      });

  iscool::schedule::initialize(delegate);

  bool second_call_called(false);
  auto second_call(
      [&second_call_called]() -> void
      {
        second_call_called = true;
      });

  auto first_call(
      [&second_call]() -> void
      {
        iscool::schedule::delayed_call(
            second_call, iscool::schedule::short_call_policy::cumulated);
      });

  iscool::schedule::delayed_call(first_call);

  EXPECT_FALSE(calls.empty());
  calls[0]();
  EXPECT_TRUE(second_call_called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, short_call_non_cumulated)
{
  std::vector<iscool::signals::void_signal_function> calls;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        calls.push_back(f);
      });

  iscool::schedule::initialize(delegate);

  bool second_call_called(false);
  auto second_call(
      [&second_call_called]() -> void
      {
        second_call_called = true;
      });

  auto first_call(
      [&second_call]() -> void
      {
        iscool::schedule::delayed_call(
            second_call, iscool::schedule::short_call_policy::non_cumulated);
      });

  iscool::schedule::delayed_call(first_call);

  EXPECT_EQ(1ull, calls.size());
  calls[0]();
  EXPECT_FALSE(second_call_called);

  EXPECT_EQ(2ull, calls.size());
  calls[1]();
  EXPECT_TRUE(second_call_called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, independent_connections)
{
  std::vector<iscool::signals::void_signal_function> calls;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        calls.push_back(f);
      });

  iscool::schedule::initialize(delegate);

  bool first_call_called(false);
  auto first_call(
      [&first_call_called]() -> void
      {
        first_call_called = true;
      });

  bool second_call_called(false);
  auto second_call(
      [&second_call_called]() -> void
      {
        second_call_called = true;
      });

  iscool::signals::connection first_connection(
      iscool::schedule::delayed_call(first_call));
  const iscool::signals::connection second_connection(
      iscool::schedule::delayed_call(second_call));

  first_connection.disconnect();
  EXPECT_TRUE(second_connection.connected());

  EXPECT_EQ(1ull, calls.size());
  calls[0]();
  EXPECT_FALSE(first_call_called);
  EXPECT_TRUE(second_call_called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, independent_immediate_calls)
{
  std::vector<iscool::signals::void_signal_function> calls;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        calls.push_back(f);
      });

  iscool::schedule::initialize(delegate);

  bool first_call_called(false);
  auto first_call(
      [&first_call_called]() -> void
      {
        first_call_called = true;
      });

  iscool::schedule::delayed_call(first_call);
  EXPECT_EQ(1ull, calls.size());
  calls[0]();
  EXPECT_TRUE(first_call_called);

  bool second_call_called(false);
  auto second_call(
      [&second_call_called]() -> void
      {
        second_call_called = true;
      });

  iscool::schedule::delayed_call(second_call);

  EXPECT_EQ(2ull, calls.size());
  calls[1]();
  EXPECT_TRUE(second_call_called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, cumulated_large)
{
  iscool::signals::void_signal_function client;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        EXPECT_FALSE(client);
        client = f;
      });

  iscool::schedule::initialize(delegate);

  std::size_t calls(0);
  const std::size_t bound(1000);
  iscool::signals::void_signal_function f;

  f = [&f, &calls]() -> void
  {
    ++calls;

    if (calls != bound)
      iscool::schedule::delayed_call(f);
  };

  iscool::schedule::delayed_call(f);

  while (calls != bound)
    {
      const std::size_t calls_at_begin(calls);

      EXPECT_TRUE(client);

      const iscool::signals::void_signal_function client_call(
          std::move(client));
      client_call();

      EXPECT_LE(calls, bound);
      EXPECT_GE(calls, calls_at_begin);
    }

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, cumulated_after_delay)
{
  std::vector<iscool::signals::void_signal_function> calls;
  auto delegate(
      [&](iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay) -> void
      {
        calls.push_back(f);
      });

  iscool::schedule::initialize(delegate);

  bool second_call_called(false);
  auto second_call(
      [&second_call_called]() -> void
      {
        second_call_called = true;
      });

  auto first_call(
      [&second_call]() -> void
      {
        iscool::schedule::delayed_call(
            second_call, iscool::schedule::short_call_policy::cumulated);
      });

  iscool::schedule::delayed_call(first_call, std::chrono::milliseconds(10));

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  EXPECT_FALSE(calls.empty());
  calls[0]();
  EXPECT_TRUE(second_call_called);

  iscool::schedule::finalize();
}
