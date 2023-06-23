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
#ifndef ISCOOL_SCHEDULE_TIMER_TPP
#define ISCOOL_SCHEDULE_TIMER_TPP

#include <iscool/time/now.hpp>

template <typename Duration>
Duration iscool::schedule::timer::get_duration() const
{
  const reference_duration current_date(time::now<reference_duration>());
  const reference_duration duration_since_resume(current_date
                                                 - _duration_reference_date);

  reference_duration duration_in_pause(0);

  if (_paused)
    duration_in_pause = current_date - _pause_date;

  const reference_duration duration(duration_since_resume - duration_in_pause);

  return std::chrono::duration_cast<Duration>(duration);
}

#endif
