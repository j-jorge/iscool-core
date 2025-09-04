// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/memory/dynamic_pool.hpp>
#include <iscool/memory/pool_signal_traits.hpp>
#include <iscool/schedule/short_call_policy.hpp>

#include <iscool/signals/signal.hpp>

#include <chrono>
#include <functional>
#include <mutex>

namespace iscool::schedule::detail
{
  class delayed_call_manager
  {
  public:
    typedef std::chrono::nanoseconds duration;

  public:
    explicit delayed_call_manager(std::size_t pool_size);

    connection schedule_call(std::function<void()> f, duration delay);

    connection schedule_call(std::function<void()> f,
                             short_call_policy policy);

    bool connected(const connection& c);
    void disconnect(const connection& c);

    void clear();

  private:
    typedef iscool::memory::dynamic_pool<
        iscool::signals::void_signal,
        iscool::memory::pool_signal_traits<iscool::signals::void_signal>>
        pool_type;

  private:
    connection schedule_cumulated(std::function<void()> f);
    connection schedule_non_cumulated(std::function<void()> f);
    connection schedule_delayed(std::function<void()> f, duration delay);

    void schedule_client(std::size_t id, duration delay);
    void schedule_client_cumulated();
    void schedule_client_non_cumulated();

    void trigger(std::size_t id, duration expected_date);
    void trigger_cumulated();
    void trigger_non_cumulated();

  private:
    iscool::signals::void_signal _short_call_cumulated;
    iscool::signals::void_signal _short_call_non_cumulated;

    pool_type _tmp_signals;

    pool_type _pool;

    bool _client_guard;
    bool _in_cumulated_loop;

    std::recursive_mutex _mutex;
  };
}
