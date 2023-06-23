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
#ifndef ISCOOL_SCHEDULE_SCALED_TIMER_TPP
#define ISCOOL_SCHEDULE_SCALED_TIMER_TPP

template <typename Duration>
Duration iscool::schedule::scaled_timer::get_duration() const
{
  const duration now(_timer.get_duration<duration>());
  const float result(_scaled_reference.count()
                     + _scale * (now - _real_reference).count());

  return std::chrono::duration_cast<Duration>(duration(duration::rep(result)));
}

#endif
