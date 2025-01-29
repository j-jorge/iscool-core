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

#include <atomic>
#include <thread>

#include <gtest/gtest.h>

TEST(iscool_schedule_delayed_call, concurrent_calls_delayed)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  std::atomic<bool> stop(false);
  std::thread scheduler_thread(
      [&stop, &scheduler]() -> void
      {
        while (!stop)
          {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            scheduler.update_interval(std::chrono::milliseconds(10));
          }
      });

  std::size_t num_calls(0);
  auto test_func(
      [&num_calls]() -> void
      {
        num_calls++;
      });

  std::atomic<bool> start(false);
  auto thread_func(
      [&start, &test_func]() -> void
      {
        while (!start)
          std::this_thread::sleep_for(std::chrono::milliseconds(10));

        iscool::schedule::delayed_call(test_func,
                                       std::chrono::milliseconds(50));
      });

  const std::size_t num_threads(100);
  std::vector<std::thread> threads;
  for (std::size_t i(0); i < num_threads; ++i)
    threads.push_back(std::thread(thread_func));

  start = true;
  for (std::thread& t : threads)
    t.join();

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  stop = true;
  scheduler_thread.join();

  EXPECT_EQ(num_calls, num_threads);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, concurrent_calls_cumulated)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  std::atomic<bool> stop(false);
  std::thread scheduler_thread(
      [&stop, &scheduler]() -> void
      {
        while (!stop)
          {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            scheduler.update_interval(std::chrono::milliseconds(10));
          }
      });

  std::size_t num_calls(0);
  auto test_func(
      [&num_calls]() -> void
      {
        num_calls++;
      });

  auto cumulated_test_func(
      [&test_func]() -> void
      {
        iscool::schedule::delayed_call(
            test_func, iscool::schedule::short_call_policy::cumulated);
      });

  std::atomic<bool> start(false);
  auto thread_func(
      [&start, &cumulated_test_func]() -> void
      {
        while (!start)
          std::this_thread::sleep_for(std::chrono::milliseconds(10));

        iscool::schedule::delayed_call(cumulated_test_func,
                                       std::chrono::milliseconds(50));
      });

  const std::size_t num_threads(100);
  std::vector<std::thread> threads;
  for (std::size_t i(0); i < num_threads; ++i)
    threads.push_back(std::thread(thread_func));

  start = true;
  for (std::thread& t : threads)
    t.join();

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  stop = true;
  scheduler_thread.join();

  EXPECT_EQ(num_calls, num_threads);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, concurrent_calls_non_cumulated)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  std::atomic<bool> stop(false);
  std::thread scheduler_thread(
      [&stop, &scheduler]() -> void
      {
        while (!stop)
          {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            scheduler.update_interval(std::chrono::milliseconds(10));
          }
      });

  std::size_t num_calls(0);
  auto test_func(
      [&num_calls]() -> void
      {
        num_calls++;
      });

  auto non_cumulated_test_func(
      [&test_func]() -> void
      {
        iscool::schedule::delayed_call(
            test_func, iscool::schedule::short_call_policy::non_cumulated);
      });

  std::atomic<bool> start(false);
  auto thread_func(
      [&start, &non_cumulated_test_func]() -> void
      {
        while (!start)
          std::this_thread::sleep_for(std::chrono::milliseconds(10));

        iscool::schedule::delayed_call(non_cumulated_test_func,
                                       std::chrono::milliseconds(50));
      });

  const std::size_t num_threads(100);
  std::vector<std::thread> threads;
  for (std::size_t i(0); i < num_threads; ++i)
    threads.push_back(std::thread(thread_func));

  start = true;
  for (std::thread& t : threads)
    t.join();

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  stop = true;
  scheduler_thread.join();

  EXPECT_EQ(num_calls, num_threads);

  iscool::schedule::finalize();
}

TEST(iscool_schedule_delayed_call, recursive_schedule_from_two_threads)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  std::atomic<bool> stop(false);
  std::thread scheduler_thread(
      [&stop, &scheduler]() -> void
      {
        while (!stop)
          {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            scheduler.update_interval(std::chrono::milliseconds(10));
          }
      });

  std::size_t num_calls(0);
  const auto test_func(
      [&num_calls]() -> void
      {
        num_calls++;
      });

  std::atomic<bool> schedule_in_first_thread(false);

  std::thread first_thread(
      [&schedule_in_first_thread, &test_func]() -> void
      {
        while (!schedule_in_first_thread)
          std::this_thread::sleep_for(std::chrono::milliseconds(10));

        iscool::schedule::delayed_call(test_func,
                                       std::chrono::milliseconds(50));
      });

  const auto join_first_thread(
      [&schedule_in_first_thread, &first_thread]() -> void
      {
        schedule_in_first_thread = true;
        first_thread.join();
      });

  iscool::schedule::delayed_call(join_first_thread,
                                 std::chrono::milliseconds(50));

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  stop = true;
  scheduler_thread.join();

  EXPECT_EQ(1, num_calls);

  iscool::schedule::finalize();
}
