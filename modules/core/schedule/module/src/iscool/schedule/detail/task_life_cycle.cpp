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
#include "iscool/schedule/detail/task_life_cycle.h"

#include "iscool/signals/implement_signal.h"

IMPLEMENT_SIGNAL(iscool::schedule::detail::task_life_cycle, complete,
                 _complete);

iscool::schedule::detail::task_life_cycle::task_life_cycle(
    task_pointer implementation)
  : _internal_state(state::created)
  , _implementation(std::move(implementation))
{
  assert(_implementation != nullptr);
  _implementation->connect_to_complete(
      std::bind(&iscool::schedule::detail::task_life_cycle::complete, this));
}

iscool::schedule::detail::task_life_cycle::~task_life_cycle()
{
  assert(!is_running());
}

void iscool::schedule::detail::task_life_cycle::start()
{
  assert(_internal_state == state::created);

  _internal_state = state::running;
  _implementation->start();
}

void iscool::schedule::detail::task_life_cycle::update()
{
  assert(is_running());
  _implementation->update();
}

void iscool::schedule::detail::task_life_cycle::abort()
{
  assert(_internal_state != state::stopped);

  _internal_state = state::stopped;
  _implementation->abort();
}

bool iscool::schedule::detail::task_life_cycle::is_running() const
{
  return _internal_state == state::running;
}

std::chrono::milliseconds
iscool::schedule::detail::task_life_cycle::get_update_interval() const
{
  assert(_internal_state != state::created);

  if (_internal_state == state::stopped)
    return task::no_update_interval;

  return _implementation->get_update_interval();
}

void iscool::schedule::detail::task_life_cycle::complete()
{
  assert(_internal_state != state::stopped);

  _internal_state = state::stopped;
  _complete();
}
