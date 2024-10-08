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
#ifndef ISCOOL_TIME_BACKWARD_DURATION_TO_UNIT_CHANGE_H
#define ISCOOL_TIME_BACKWARD_DURATION_TO_UNIT_CHANGE_H

#include <chrono>

namespace iscool
{
  namespace time
  {
    template <class TargetDuration, class Rep, class Period>
    TargetDuration backward_duration_to_unit_change(
        const std::chrono::duration<Rep, Period>& duration);
  }
}

#include <iscool/time/detail/backward_duration_to_unit_change.tpp>

#endif
