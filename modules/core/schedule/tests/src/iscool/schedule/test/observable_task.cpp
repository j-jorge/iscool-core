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
#include <iscool/schedule/test/observable_task.hpp>

#include <iscool/schedule/test/task_activity_report.hpp>

iscool::schedule::test::observable_task::observable_task(
    const std::chrono::milliseconds& update_interval,
    task_activity_report& report)
  : iscool::schedule::task("observable_task")
  , _update_interval(update_interval)
  , _report(report)
{}

iscool::schedule::test::observable_task::observable_task(
    std::chrono::milliseconds& update_interval, task_activity_report& report,
    iscool::signals::signal<void()>& complete)
  : iscool::schedule::task("observable_task")
  , _update_interval(update_interval)
  , _report(report)
  , _completion_connection(complete.connect(
        std::bind(&iscool::schedule::test::observable_task::complete, this)))
{}

void iscool::schedule::test::observable_task::implementation_start()
{
  ++_report.start_calls;
}

void iscool::schedule::test::observable_task::implementation_update()
{
  ++_report.update_calls;
}

void iscool::schedule::test::observable_task::implementation_abort()
{
  ++_report.abort_calls;
}

std::chrono::milliseconds
iscool::schedule::test::observable_task ::implementation_get_update_interval()
    const
{
  return _update_interval;
}
