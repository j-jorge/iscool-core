// SPDX-License-Identifier: Apache-2.0
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
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
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
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
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
  std::function<void()> callback;
  auto delegate(
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
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
  std::function<void()> callback;
  auto delegate(
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
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
  std::vector<std::function<void()>> calls;
  auto delegate(
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
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

  iscool::schedule::connection second_call_connection;
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
  std::vector<std::function<void()>> calls;
  auto delegate(
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
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
  std::vector<std::function<void()>> calls;
  auto delegate(
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
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
  std::vector<std::function<void()>> calls;
  auto delegate(
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
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

  iscool::schedule::connection first_connection(
      iscool::schedule::delayed_call(first_call));
  const iscool::schedule::connection second_connection(
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
  std::vector<std::function<void()>> calls;
  auto delegate(
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
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
  std::function<void()> client;
  auto delegate(
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
      {
        EXPECT_FALSE(client);
        client = f;
      });

  iscool::schedule::initialize(delegate);

  std::size_t calls(0);
  const std::size_t bound(1000);
  std::function<void()> f;

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

      const std::function<void()> client_call(std::move(client));
      client_call();

      EXPECT_LE(calls, bound);
      EXPECT_GE(calls, calls_at_begin);
    }

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, cumulated_after_delay)
{
  std::vector<std::function<void()>> calls;
  auto delegate(
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
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
