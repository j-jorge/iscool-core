// SPDX-License-Identifier: Apache-2.0
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

// This test does not test much but is used with ThreadSanitizer to ensure
// there is no data race between multiple threads scheduling calls and
// cancelling them
TEST(iscool_schedule_delayed_call, concurrent_calls_delayed_disconnect)
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

  auto test_func(
      []() -> void
      {
      });

  std::atomic<bool> start(false);
  auto thread_func(
      [&start, &test_func]() -> void
      {
        while (!start)
          std::this_thread::sleep_for(std::chrono::milliseconds(10));

        iscool::schedule::connection c = iscool::schedule::delayed_call(
            test_func, std::chrono::milliseconds(50));
        c.disconnect();
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

// This test does not test much but is used with ThreadSanitizer to ensure
// there is no data race between multiple threads scheduling calls and
// cancelling them
TEST(iscool_schedule_delayed_call, concurrent_calls_cumulated_disconnect)
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

  auto test_func(
      []() -> void
      {
      });

  auto cumulated_test_func(
      [&test_func]() -> void
      {
        iscool::schedule::connection c = iscool::schedule::delayed_call(
            test_func, iscool::schedule::short_call_policy::cumulated);
        c.disconnect();
      });

  std::atomic<bool> start(false);
  auto thread_func(
      [&start, &cumulated_test_func]() -> void
      {
        while (!start)
          std::this_thread::sleep_for(std::chrono::milliseconds(10));

        iscool::schedule::connection c = iscool::schedule::delayed_call(
            cumulated_test_func, std::chrono::milliseconds(50));
        c.disconnect();
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

// This test does not test much but is used with ThreadSanitizer to ensure
// there is no data race between multiple threads scheduling calls and
// cancelling them
TEST(iscool_schedule_delayed_call, concurrent_calls_non_cumulated_disconnect)
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

  auto test_func(
      []() -> void
      {
      });

  auto non_cumulated_test_func(
      [&test_func]() -> void
      {
        iscool::schedule::connection c = iscool::schedule::delayed_call(
            test_func, iscool::schedule::short_call_policy::non_cumulated);
        c.disconnect();
      });

  std::atomic<bool> start(false);
  auto thread_func(
      [&start, &non_cumulated_test_func]() -> void
      {
        while (!start)
          std::this_thread::sleep_for(std::chrono::milliseconds(10));

        iscool::schedule::connection c = iscool::schedule::delayed_call(
            non_cumulated_test_func, std::chrono::milliseconds(50));
        c.disconnect();
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
