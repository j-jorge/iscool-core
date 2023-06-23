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
#include "iscool/schedule/delayed_call.h"

#include "iscool/schedule/detail/call_later.h"

#include <cassert>

iscool::signals::connection
iscool::schedule::delayed_call(iscool::signals::void_signal_function f,
                               short_call_policy policy)
{
  assert(f);

  return detail::call_manager.schedule_call(f, policy);
}

iscool::signals::connection
iscool::schedule::delayed_call(iscool::signals::void_signal_function f,
                               std::chrono::nanoseconds delay)
{
  assert(f);
  assert(delay.count() >= 0);

  if (delay == std::chrono::nanoseconds::zero())
    return delayed_call(f, short_call_policy::non_cumulated);

  return detail::call_manager.schedule_call(f, delay);
}
