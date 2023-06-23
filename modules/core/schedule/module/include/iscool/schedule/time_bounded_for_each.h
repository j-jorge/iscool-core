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
#ifndef ISCOOL_SCHEDULE_TIME_BOUNDED_FOR_EACH_H
#define ISCOOL_SCHEDULE_TIME_BOUNDED_FOR_EACH_H

#include "iscool/signals/declare_signal.h"
#include "iscool/signals/scoped_connection.h"

#include <chrono>
#include <functional>

namespace iscool
{
  namespace schedule
  {
    class time_bounded_for_each
    {
      DECLARE_VOID_SIGNAL(completed, _completed);

    private:
      typedef std::chrono::milliseconds duration_type;

    public:
      time_bounded_for_each();
      ~time_bounded_for_each();

      void abort();

      template <typename Iterator, typename Function, typename Rep,
                typename Period>
      void operator()(Iterator first, Iterator last, Function f,
                      std::chrono::duration<Rep, Period> time_limit);

    private:
      void schedule_loop();
      void loop();

    private:
      duration_type _time_limit;
      std::size_t _next_index;
      std::vector<std::function<void()>> _calls;
      bool _looping;
      iscool::signals::scoped_connection _loop_connection;
    };
  }
}

#include "iscool/schedule/detail/time_bounded_for_each.tpp"

#endif
