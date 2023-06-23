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
#ifndef ISCOOL_SCHEDULE_WORKER_TPP
#define ISCOOL_SCHEDULE_WORKER_TPP

template <typename TaskType, typename... Args>
typename iscool::schedule::worker::handle
iscool::schedule::worker::run(Args... arguments)
{
  detail::task_life_cycle* const task(
      new detail::task_life_cycle(detail::task_life_cycle::task_pointer(
          new TaskType(std::forward<Args>(arguments)...))));

  return worker::handle(new worker(task_pointer(task)));
}

#endif
