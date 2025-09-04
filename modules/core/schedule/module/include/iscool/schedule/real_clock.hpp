// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/schedule/clock.hpp>
#include <iscool/schedule/scoped_connection.hpp>

#include <chrono>

namespace iscool::schedule
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
    scoped_connection _beat_connection;
  };
}

#include <iscool/schedule/detail/real_clock.tpp>
