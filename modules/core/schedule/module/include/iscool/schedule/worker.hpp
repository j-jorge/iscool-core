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
#ifndef ISCOOL_SCHEDULE_WORKER_H
#define ISCOOL_SCHEDULE_WORKER_H

#include <iscool/schedule/detail/task_life_cycle.hpp>

#include <iscool/signals/scoped_connection.hpp>
#include <iscool/signals/void_signal_function.hpp>

#include <memory>

namespace iscool
{
  namespace schedule
  {
    class worker
    {
    public:
      typedef std::unique_ptr<worker> handle;

    public:
      template <typename TaskType, typename... Args>
      static handle run(Args... arguments);

      ~worker();

      iscool::signals::connection
      connect_to_complete(iscool::signals::void_signal_function f);

    private:
      typedef std::shared_ptr<detail::task_life_cycle> task_pointer;

    private:
      explicit worker(task_pointer task);

      void start_task();
      void update_task();
      void complete_task();
      void schedule_next_update();
      void clear();

      worker(const worker&) = delete;
      worker& operator=(const worker&) = delete;

    private:
      task_pointer _task;
      iscool::signals::scoped_connection _update_connection;
      iscool::signals::scoped_connection _complete_connection;
    };
  }
}

#include <iscool/schedule/detail/worker.tpp>

#endif
