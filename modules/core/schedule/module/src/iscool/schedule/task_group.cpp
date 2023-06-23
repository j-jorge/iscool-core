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
#include "iscool/schedule/task_group.h"

iscool::schedule::task_group::task_group() = default;
iscool::schedule::task_group::~task_group() = default;

void iscool::schedule::task_group::pop(std::size_t id)
{
  assert(id < _tasks.size());
  assert(_tasks[id] != nullptr);
  _tasks[id] = nullptr;
}

std::size_t iscool::schedule::task_group::get_available_task_index()
{
  const std::size_t count(_tasks.size());

  for (std::size_t i(0); i != count; ++i)
    if (_tasks[i] == nullptr)
      return i;

  _tasks.emplace_back();
  return count;
}
