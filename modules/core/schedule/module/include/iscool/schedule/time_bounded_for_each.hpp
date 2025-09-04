// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/schedule/scoped_connection.hpp>

#include <iscool/signals/declare_signal.hpp>

#include <chrono>
#include <functional>

namespace iscool::schedule
{
  class time_bounded_for_each
  {
    DECLARE_VOID_SIGNAL(completed, _completed)

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
    scoped_connection _loop_connection;
  };
}

#include <iscool/schedule/detail/time_bounded_for_each.tpp>
