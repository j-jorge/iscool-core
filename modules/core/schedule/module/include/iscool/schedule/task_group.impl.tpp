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
#ifndef ISCOOL_SCHEDULE_TASK_GROUP_IMPL_TPP
#define ISCOOL_SCHEDULE_TASK_GROUP_IMPL_TPP

template <typename TaskType, typename... Args>
void iscool::schedule::task_group::run(Args&&... args)
{
  const std::size_t i(get_available_task_index());

  worker::handle handle(worker::run<TaskType>(std::forward<Args>(args)...));
  handle->connect_to_complete(std::bind(&task_group::pop, this, i));

  _tasks[i] = std::move(handle);
}

#endif
