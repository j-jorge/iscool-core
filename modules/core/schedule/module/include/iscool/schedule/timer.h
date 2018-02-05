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
#ifndef ISCOOL_SCHEDULE_TIMER_H
#define ISCOOL_SCHEDULE_TIMER_H

#include <chrono>

namespace iscool
{
    namespace schedule
    {
        class timer
        {
        public:
            timer();

            void reset();
            void pause();
            void resume();

            template< typename Duration >
            Duration get_duration() const;

        private:
            typedef std::chrono::milliseconds reference_duration;

        private:
            bool _paused; 
            reference_duration _duration_reference_date;
            reference_duration _pause_date;
        };
    }
}

#include "iscool/schedule/detail/timer.tpp"

#endif
