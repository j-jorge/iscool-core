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
#include "iscool/schedule/time_bounded_for_each.h"
#include "iscool/schedule/manual_scheduler.h"
#include "iscool/schedule/setup.h"

#include <thread>

#include <gtest/gtest.h>

class iscool_schedule_time_bounded_for_each_test : public ::testing::Test
{
public:
  iscool_schedule_time_bounded_for_each_test();
  ~iscool_schedule_time_bounded_for_each_test();

protected:
  void process_item(std::size_t value);
  void sleep(std::size_t milliseconds);

protected:
  iscool::schedule::manual_scheduler _scheduler;
  std::vector<std::size_t> _calls;
};

iscool_schedule_time_bounded_for_each_test ::
    iscool_schedule_time_bounded_for_each_test()
{
  iscool::schedule::initialize(_scheduler.get_delayed_call_delegate());
}

iscool_schedule_time_bounded_for_each_test ::
    ~iscool_schedule_time_bounded_for_each_test()
{
  iscool::schedule::finalize();
}

void iscool_schedule_time_bounded_for_each_test::process_item(
    std::size_t value)
{
  sleep(value);
  _calls.push_back(value);
}

void iscool_schedule_time_bounded_for_each_test::sleep(
    std::size_t milliseconds)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

TEST_F(iscool_schedule_time_bounded_for_each_test, one_pass)
{
  const std::vector<std::size_t> values = { 1, 20, 3 };
  auto f(
      [this](std::size_t value) -> void
      {
        process_item(value);
      });

  iscool::schedule::time_bounded_for_each loop;
  loop(values.begin(), values.end(), f, std::chrono::seconds(1));
  _scheduler.update_interval(std::chrono::milliseconds(500));

  EXPECT_EQ(values, _calls);
}

TEST_F(iscool_schedule_time_bounded_for_each_test, two_passes)
{
  const std::vector<std::size_t> values = { 300, 400, 500 };
  auto f(
      [this](std::size_t value) -> void
      {
        process_item(value);
      });

  iscool::schedule::time_bounded_for_each loop;
  loop(values.begin(), values.end(), f, std::chrono::milliseconds(500));
  sleep(50);
  _scheduler.update_interval(std::chrono::milliseconds(50));

  const std::vector<std::size_t> expected_first_pass = { 300, 400 };
  EXPECT_EQ(expected_first_pass, _calls);

  sleep(50);
  _scheduler.update_interval(std::chrono::milliseconds(50));
  EXPECT_EQ(values, _calls);
}

TEST_F(iscool_schedule_time_bounded_for_each_test, non_void_return_type)
{
  const std::vector<std::size_t> values = { 1 };
  auto f(
      [this](std::size_t value) -> std::string
      {
        process_item(value);
        return "";
      });

  iscool::schedule::time_bounded_for_each loop;
  loop(values.begin(), values.end(), f, std::chrono::seconds(1));
  _scheduler.update_interval(std::chrono::milliseconds(500));

  EXPECT_EQ(values, _calls);
}

TEST_F(iscool_schedule_time_bounded_for_each_test, process_at_least_one)
{
  const std::vector<std::size_t> values = { 5, 6, 3 };
  auto f(
      [this](std::size_t value) -> void
      {
        process_item(value);
      });

  iscool::schedule::time_bounded_for_each loop;
  loop(values.begin(), values.end(), f, std::chrono::milliseconds(0));
  _scheduler.update_interval(std::chrono::milliseconds(500));

  const std::vector<std::size_t> expected = { 5 };
  EXPECT_EQ(expected, _calls);
}

TEST_F(iscool_schedule_time_bounded_for_each_test, completion_signal)
{
  const std::vector<std::size_t> values = { 200, 400, 500 };
  auto f(
      [this](std::size_t value) -> void
      {
        process_item(value);
      });

  iscool::schedule::time_bounded_for_each loop;

  bool completed(false);
  loop.connect_to_completed(
      [&completed]() -> void
      {
        completed = true;
      });

  loop(values.begin(), values.end(), f, std::chrono::milliseconds(500));
  _scheduler.update_interval(std::chrono::milliseconds(500));
  EXPECT_FALSE(completed);

  _scheduler.update_interval(std::chrono::milliseconds(500));
  EXPECT_TRUE(completed);
}

TEST_F(iscool_schedule_time_bounded_for_each_test, abort)
{
  const std::vector<std::size_t> values = { 1, 20, 3 };
  iscool::schedule::time_bounded_for_each loop;

  auto f(
      [this, &loop](std::size_t value) -> void
      {
        process_item(value);
        loop.abort();
      });

  loop(values.begin(), values.end(), f, std::chrono::seconds(1));
  _scheduler.update_interval(std::chrono::milliseconds(500));

  const std::vector<std::size_t> expected = { 1 };
  EXPECT_EQ(expected, _calls);
}

TEST_F(iscool_schedule_time_bounded_for_each_test, abort_immediately)
{
  const std::vector<std::size_t> values = { 1, 20, 3 };
  iscool::schedule::time_bounded_for_each loop;

  bool called(false);
  auto f(
      [&called](std::size_t value) -> void
      {
        called = true;
      });

  loop(values.begin(), values.end(), f, std::chrono::seconds(1));
  loop.abort();
  _scheduler.update_interval(std::chrono::milliseconds(500));

  EXPECT_FALSE(called);
}

TEST_F(iscool_schedule_time_bounded_for_each_test, late_abort)
{
  const std::vector<std::size_t> values = { 1, 1, 1, 1, 2, 3, 3, 3, 3 };
  iscool::schedule::time_bounded_for_each loop;

  auto f(
      [this, &loop](std::size_t value) -> void
      {
        process_item(value);

        if (value == 2)
          loop.abort();
      });

  loop(values.begin(), values.end(), f, std::chrono::seconds(1));
  _scheduler.update_interval(std::chrono::milliseconds(500));

  const std::vector<std::size_t> expected = { 1, 1, 1, 1, 2 };
  EXPECT_EQ(expected, _calls);
}

TEST_F(iscool_schedule_time_bounded_for_each_test, abort_in_break)
{
  const std::vector<std::size_t> values = { 1, 1, 1, 1, 20, 3, 3, 3, 3 };
  iscool::schedule::time_bounded_for_each loop;

  auto f(
      [this, &loop](std::size_t value) -> void
      {
        process_item(value);
      });

  loop(values.begin(), values.end(), f, std::chrono::milliseconds(20));
  sleep(20);
  _scheduler.update_interval(std::chrono::milliseconds(20));

  loop.abort();
  _scheduler.update_interval(std::chrono::milliseconds(500));

  const std::vector<std::size_t> expected = { 1, 1, 1, 1, 20 };
  EXPECT_EQ(expected, _calls);
}

TEST_F(iscool_schedule_time_bounded_for_each_test, abort_after)
{
  const std::vector<std::size_t> values = { 1, 1, 2, 3 };
  iscool::schedule::time_bounded_for_each loop;

  auto f(
      [this, &loop](std::size_t value) -> void
      {
        process_item(value);
      });

  loop(values.begin(), values.end(), f, std::chrono::seconds(1));
  _scheduler.update_interval(std::chrono::milliseconds(500));
  loop.abort();

  const std::vector<std::size_t> expected = { 1, 1, 2, 3 };
  EXPECT_EQ(expected, _calls);
}
