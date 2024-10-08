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
#ifndef ISCOOL_SCHEDULE_MANUAL_SCHEDULER_H
#define ISCOOL_SCHEDULE_MANUAL_SCHEDULER_H

#include <iscool/schedule/delayed_call_delegate.hpp>

#include <mutex>
#include <vector>

namespace iscool
{
  namespace schedule
  {
    class manual_scheduler
    {
    public:
      manual_scheduler();

      delayed_call_delegate get_delayed_call_delegate();

      std::chrono::nanoseconds delay_until_next_non_immediate_call() const;

      void update_interval(std::chrono::nanoseconds interval);

    private:
      struct call
      {
        std::chrono::nanoseconds at_date;
        iscool::signals::void_signal_function function;
      };

    private:
      void schedule_call(iscool::signals::void_signal_function f,
                         std::chrono::nanoseconds delay);

    private:
      std::chrono::nanoseconds _current_date;
      std::vector<call> _calls;
      std::mutex _mutex;
    };
  }
}

#endif
