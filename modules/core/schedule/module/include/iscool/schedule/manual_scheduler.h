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

#include "iscool/schedule/delayed_call_delegate.h"

#include <map>

namespace iscool
{
    namespace schedule
    {
        class manual_scheduler
        {
        public:
            manual_scheduler();
            
            delayed_call_delegate get_delayed_call_delegate();

            void update_interval( std::chrono::milliseconds interval );

        private:
            typedef
            std::multimap< std::size_t, iscool::signals::void_signal_function >
            call_map;
            
        private:
            void schedule_call
            ( iscool::signals::void_signal_function f,
              std::chrono::milliseconds delay );
            
        private:
            std::chrono::milliseconds _current_date;
            call_map _calls;
        };
    }
}

#endif
