// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/schedule/detail/task_life_cycle.hpp>
#include <iscool/schedule/scoped_connection.hpp>

#include <iscool/signals/scoped_connection.hpp>

#include <functional>
#include <memory>

namespace iscool::schedule
{
  class worker
  {
  public:
    typedef std::unique_ptr<worker> handle;

  public:
    template <typename TaskType, typename... Args>
    static handle run(Args... arguments);

    ~worker();

    iscool::signals::connection connect_to_complete(std::function<void()> f);

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
    scoped_connection _update_connection;
    iscool::signals::scoped_connection _complete_connection;
  };
}

#include <iscool/schedule/detail/worker.tpp>
