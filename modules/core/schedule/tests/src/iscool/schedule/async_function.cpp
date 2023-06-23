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
#include "iscool/schedule/async_function.h"
#include "iscool/schedule/manual_scheduler.h"
#include "iscool/schedule/setup.h"

#include "iscool/signals/signal.h"
#include "iscool/signals/signal.impl.tpp"

#include "gtest/gtest.h"

TEST(iscool_schedule_async_function, is_delayed)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  bool called(false);
  iscool::schedule::async_function<void()> f(
      [&called]() -> void
      {
        called = true;
      });

  f();
  EXPECT_FALSE(called);

  scheduler.update_interval(std::chrono::milliseconds::zero());
  EXPECT_TRUE(called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_async_function, fonctor)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  class F
  {
  public:
    explicit F(bool& result)
      : _result(result)
    {}

    void operator()()
    {
      _result = true;
    }

  private:
    bool& _result;
  };

  bool called(false);
  F function(called);
  iscool::schedule::async_function<void()> f(function);

  f();
  scheduler.update_interval(std::chrono::milliseconds::zero());
  EXPECT_TRUE(called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_async_function, destructor)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  bool called(false);
  {
    iscool::schedule::async_function<void()> f(
        [&called]() -> void
        {
          called = true;
        });

    f();
  }

  scheduler.update_interval(std::chrono::milliseconds::zero());
  EXPECT_FALSE(called);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_async_function, copy)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  std::size_t calls(0);
  iscool::schedule::async_function<void()> f(
      [&calls]() -> void
      {
        ++calls;
      });

  iscool::schedule::async_function<void()> g(f);

  f();
  g();

  EXPECT_EQ(0ull, calls);
  scheduler.update_interval(std::chrono::milliseconds::zero());
  EXPECT_EQ(2ull, calls);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_async_function, assignment)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  std::size_t calls(0);
  iscool::schedule::async_function<void()> f;
  iscool::schedule::async_function<void()> g(
      [&calls]() -> void
      {
        ++calls;
      });

  f = g;

  f();
  g();

  EXPECT_EQ(0ull, calls);
  scheduler.update_interval(std::chrono::milliseconds::zero());
  EXPECT_EQ(2ull, calls);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_async_function, empty)
{
  iscool::schedule::async_function<void()> f;
  iscool::schedule::async_function<void()> g(
      []() -> void
      {
      });

  EXPECT_TRUE(f.empty());
  EXPECT_FALSE(g.empty());
  g = f;
  EXPECT_TRUE(g.empty());
}

TEST(iscool_schedule_async_function, arguments)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  int a(0);
  std::string b;
  float c(0);

  iscool::schedule::async_function<void(int, std::string, float)> f(
      [&a, &b, &c](int arg1, std::string arg2, float arg3) -> void
      {
        a = arg1;
        b = arg2;
        c = arg3;
      });

  f(24, "yep", 2.f);

  scheduler.update_interval(std::chrono::milliseconds::zero());

  EXPECT_EQ(24, a);
  EXPECT_EQ("yep", b);
  EXPECT_EQ(2.f, c);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_async_function, multiple_calls)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  std::vector<std::size_t> values(0);
  iscool::schedule::async_function<void(std::size_t)> f(
      [&values](std::size_t i) -> void
      {
        values.push_back(i);
      });

  f(1);
  f(12);

  EXPECT_TRUE(values.empty());
  scheduler.update_interval(std::chrono::milliseconds::zero());
  EXPECT_EQ(2ull, values.size());

  EXPECT_EQ(1ull, values[0]);
  EXPECT_EQ(12ull, values[1]);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_async_function, bind)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  std::size_t value(0);
  iscool::schedule::async_function<void(std::size_t)> f(
      [&value](std::size_t i) -> void
      {
        value = i;
      });

  auto g(std::bind<void>(f, std::placeholders::_1));
  g(72);

  EXPECT_EQ(0ull, value);
  scheduler.update_interval(std::chrono::milliseconds::zero());
  EXPECT_EQ(72ull, value);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_async_function, signal)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  std::size_t value(0);
  iscool::schedule::async_function<void(std::size_t)> f(
      [&value](std::size_t i) -> void
      {
        value = i;
      });

  iscool::signals::signal<void(std::size_t)> signal;
  iscool::signals::connection connection(signal.connect(f));

  signal(48);
  EXPECT_EQ(0ull, value);
  scheduler.update_interval(std::chrono::milliseconds::zero());
  EXPECT_EQ(48ull, value);

  signal(96);
  scheduler.update_interval(std::chrono::milliseconds::zero());
  EXPECT_EQ(96ull, value);

  connection.disconnect();
  signal(84);
  scheduler.update_interval(std::chrono::milliseconds::zero());
  EXPECT_EQ(96ull, value);

  iscool::schedule::finalize();
}
