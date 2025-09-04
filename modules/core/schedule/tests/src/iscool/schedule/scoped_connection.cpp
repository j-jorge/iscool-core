// SPDX-License-Identifier: Apache-2.0
#include <iscool/schedule/delayed_call.hpp>
#include <iscool/schedule/scoped_connection.hpp>
#include <iscool/schedule/setup.hpp>

#include <vector>

#include <gtest/gtest.h>

TEST(iscool_schedule_scoped_connection, disconnect_on_disconnect)
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

  iscool::schedule::scoped_connection c = iscool::schedule::delayed_call(f);
  c.disconnect();

  EXPECT_TRUE(callback);

  callback();

  EXPECT_FALSE(called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_scoped_connection, disconnect_out_of_scope)
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

  {
    iscool::schedule::scoped_connection c = iscool::schedule::delayed_call(f);
  }

  EXPECT_TRUE(callback);

  callback();

  EXPECT_FALSE(called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_scoped_connection, disconnect_assign_empty)
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

  iscool::schedule::scoped_connection c = iscool::schedule::delayed_call(f);
  c = iscool::schedule::scoped_connection();

  EXPECT_TRUE(callback);

  callback();

  EXPECT_FALSE(called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_scoped_connection, disconnect_assign)
{
  std::function<void()> callback;
  auto delegate(
      [&](std::function<void()> f, std::chrono::nanoseconds delay) -> void
      {
        callback = f;
      });

  iscool::schedule::initialize(delegate);

  int counter = 0;

  iscool::schedule::scoped_connection c1 = iscool::schedule::delayed_call(
      [&counter]()
      {
        counter += 1;
      });
  iscool::schedule::scoped_connection c2 = iscool::schedule::delayed_call(
      [&counter]()
      {
        counter += 2;
      });
  c1 = std::move(c2);

  EXPECT_TRUE(c1.connected());
  EXPECT_FALSE(c2.connected());

  EXPECT_TRUE(callback);

  callback();

  EXPECT_EQ(2, counter);

  iscool::schedule::finalize();
}
