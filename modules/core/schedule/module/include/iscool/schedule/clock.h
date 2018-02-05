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
#ifndef ISCOOL_SCHEDULE_CLOCK_H
#define ISCOOL_SCHEDULE_CLOCK_H

#include "iscool/signals/signal.h"

namespace iscool
{
    namespace schedule
    {
        template< typename Tick >
        class clock
        {
        public:
            virtual ~clock() = default;

            iscool::signals::connection
            connect_to_tick( iscool::signals::void_signal_function f );

            Tick get_date() const;

        protected:
            void trigger_tick_signal() const;

        private:
            virtual Tick implementation_get_date() const = 0;

        private:
            iscool::signals::void_signal _tick;
        };
    }
}

#include "iscool/schedule/detail/clock.tpp"

#endif
