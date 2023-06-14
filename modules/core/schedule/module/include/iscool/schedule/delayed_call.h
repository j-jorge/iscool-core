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
#ifndef ISCOOL_SCHEDULE_DELAYED_CALL_H
#define ISCOOL_SCHEDULE_DELAYED_CALL_H

#include "iscool/schedule/short_call_policy.h"
#include "iscool/signals/connection.h"
#include "iscool/signals/void_signal_function.h"

#include <chrono>

namespace iscool
{
    namespace schedule
    {
        iscool::signals::connection delayed_call
        ( iscool::signals::void_signal_function f,
          short_call_policy policy = short_call_policy::cumulated );

        iscool::signals::connection delayed_call
        ( iscool::signals::void_signal_function f,
          std::chrono::nanoseconds delay );

        template< typename Rep, typename Period >
        iscool::signals::connection delayed_call
        ( iscool::signals::void_signal_function f,
          std::chrono::duration< Rep, Period > delay );

    }
}

#include "iscool/schedule/detail/delayed_call.tpp"

#endif
