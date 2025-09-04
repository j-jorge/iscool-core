// SPDX-License-Identifier: Apache-2.0
#include <iscool/schedule/delayed_call.hpp>

#include <iscool/schedule/detail/call_later.hpp>

#include <cassert>

iscool::schedule::connection
iscool::schedule::delayed_call(std::function<void()> f,
                               short_call_policy policy)
{
  assert(f);

  return detail::call_manager.schedule_call(std::move(f), policy);
}

iscool::schedule::connection
iscool::schedule::delayed_call(std::function<void()> f,
                               std::chrono::nanoseconds delay)
{
  assert(f);
  assert(delay.count() >= 0);

  if (delay == std::chrono::nanoseconds::zero())
    return delayed_call(std::move(f), short_call_policy::non_cumulated);

  return detail::call_manager.schedule_call(std::move(f), delay);
}
