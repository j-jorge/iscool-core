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
#ifndef ISCOOL_SCHEDULE_REAL_CLOCK_H
#define ISCOOL_SCHEDULE_REAL_CLOCK_H

#include <iscool/schedule/clock.hpp>
#include <iscool/signals/scoped_connection.hpp>

#include <chrono>

namespace iscool
{
  namespace schedule
  {
    template <typename Tick>
    class real_clock : public clock<Tick>
    {
    public:
      template <typename Rep, typename Period>
      explicit real_clock(std::chrono::duration<Rep, Period> beat);

    private:
      Tick implementation_get_date() const override;

    private:
      template <typename Rep, typename Period>
      void schedule_beat(std::chrono::duration<Rep, Period> beat);
      void check_tick_change();

      real_clock(real_clock<Tick>&) = delete;
      real_clock<Tick>& operator=(real_clock<Tick>) = delete;

    private:
      Tick _last_tick;
      iscool::signals::scoped_connection _beat_connection;
    };
  }
}

#include <iscool/schedule/detail/real_clock.tpp>

#endif
