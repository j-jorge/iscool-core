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
#ifndef ISCOOL_SCHEDULE_REAL_CLOCK_TPP
#define ISCOOL_SCHEDULE_REAL_CLOCK_TPP

#include "iscool/schedule/delayed_call.h"
#include "iscool/time/now.h"

template <typename Tick>
template <typename Rep, typename Period>
iscool::schedule::real_clock<Tick>::real_clock(
    std::chrono::duration<Rep, Period> beat)
  : _last_tick(time::now<Tick>())
{
  schedule_beat(beat);
}

template <typename Tick>
Tick iscool::schedule::real_clock<Tick>::implementation_get_date() const
{
  return time::now<Tick>();
}

template <typename Tick>
template <typename Rep, typename Period>
void iscool::schedule::real_clock<Tick>::schedule_beat(
    std::chrono::duration<Rep, Period> beat)
{
  auto f(
      [this, beat]() -> void
      {
        schedule_beat(beat);
        check_tick_change();
      });

  _beat_connection = delayed_call(f, beat);
}

template <typename Tick>
void iscool::schedule::real_clock<Tick>::check_tick_change()
{
  const Tick now{ this->get_date() };

  if (now == _last_tick)
    return;

  _last_tick = now;
  this->trigger_tick_signal();
}

#endif
