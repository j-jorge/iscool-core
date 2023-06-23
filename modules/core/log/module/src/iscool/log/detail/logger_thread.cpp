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
#include "iscool/log/detail/logger_thread.h"

#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

namespace iscool
{
  namespace log
  {
    namespace detail
    {
      static void logger_thread_loop();

      static std::thread logger_thread;
      static std::mutex logger_thread_state_mutex;
      static std::condition_variable queue_updated;

      static std::vector<std::function<void()>> logger_queue;
      static bool exit_logger_thread;
    }
  }
}

void iscool::log::detail::queue_in_logger_thread(std::function<void()> f)
{
  if (logger_thread.get_id() == std::thread::id())
    {
      exit_logger_thread = false;
      logger_thread = std::thread(&logger_thread_loop);
    }

  {
    const std::unique_lock<std::mutex> lock(logger_thread_state_mutex);
    logger_queue.emplace_back(std::move(f));
  }

  queue_updated.notify_one();
}

void iscool::log::detail::stop_logger_thread()
{
  {
    const std::unique_lock<std::mutex> lock(logger_thread_state_mutex);
    exit_logger_thread = true;
  }

  queue_updated.notify_one();

  if (logger_thread.joinable())
    logger_thread.join();
}

void iscool::log::detail::logger_thread_loop()
{
  while (true)
    {
      std::unique_lock<std::mutex> lock(logger_thread_state_mutex);

      queue_updated.wait(lock);

      if (exit_logger_thread)
        break;

      for (const std::function<void()>& f : logger_queue)
        f();

      logger_queue.clear();
    }
}
