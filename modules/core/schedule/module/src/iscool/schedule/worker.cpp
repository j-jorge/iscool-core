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
#include <iscool/schedule/worker.hpp>

#include <iscool/schedule/delayed_call.hpp>

iscool::schedule::worker::~worker()
{
  clear();
}

iscool::signals::connection iscool::schedule::worker::connect_to_complete(
    std::function<void()> f)
{
  assert(_task != nullptr);
  return _task->connect_to_complete(f);
}

iscool::schedule::worker::worker(task_pointer task)
  : _task{ std::move(task) }
{
  _update_connection = iscool::schedule::delayed_call(
      std::bind(&iscool::schedule::worker::start_task, this));
  _complete_connection = _task->connect_to_complete(
      std::bind(&iscool::schedule::worker::complete_task, this));
}

void iscool::schedule::worker::start_task()
{
  _update_connection.disconnect();

  task_pointer task(_task);
  task->start();

  if (task->is_running())
    schedule_next_update();
}

void iscool::schedule::worker::update_task()
{
  assert(_task != nullptr);

  _update_connection.disconnect();

  task_pointer task(_task);
  task->update();

  if (!task->is_running())
    return;

  schedule_next_update();
}

void iscool::schedule::worker::complete_task()
{
  _update_connection.disconnect();
}

void iscool::schedule::worker::schedule_next_update()
{
  assert(!_update_connection.connected());

  const std::chrono::milliseconds update_interval{
    _task->get_update_interval()
  };

  if (update_interval == task::no_update_interval)
    return;

  _update_connection = iscool::schedule::delayed_call(
      std::bind(&iscool::schedule::worker::update_task, this),
      update_interval);
}

void iscool::schedule::worker::clear()
{
  assert(_task != nullptr);

  if (_task->is_running())
    {
      _task->abort();
      _task = nullptr;
    }

  _update_connection.disconnect();
}
