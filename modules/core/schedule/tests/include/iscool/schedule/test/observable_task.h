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
#ifndef ISCOOL_SCHEDULE_TEST_OBSERVERVABLE_TASK_H
#define ISCOOL_SCHEDULE_TEST_OBSERVERVABLE_TASK_H

#include "iscool/schedule/task.h"
#include "iscool/signals/scoped_connection.h"
#include "iscool/signals/signal.h"

namespace iscool
{
  namespace schedule
  {
    namespace test
    {
      struct task_activity_report;

      class observable_task : public iscool::schedule::task
      {
      public:
        observable_task(const std::chrono::milliseconds& update_interval,
                        task_activity_report& report);
        observable_task(std::chrono::milliseconds& update_interval,
                        task_activity_report& report,
                        iscool::signals::signal<void()>& complete);

        void implementation_start() override;
        void implementation_update() override;
        void implementation_abort() override;
        std::chrono::milliseconds
        implementation_get_update_interval() const override;

      private:
        const std::chrono::milliseconds& _update_interval;
        task_activity_report& _report;
        iscool::signals::scoped_connection _completion_connection;
      };
    }
  }
}

#endif
