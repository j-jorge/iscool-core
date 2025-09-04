// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/schedule/connection.hpp>
#include <iscool/schedule/short_call_policy.hpp>

#include <chrono>
#include <functional>

namespace iscool::schedule
{
  connection
  delayed_call(std::function<void()> f,
               short_call_policy policy = short_call_policy::cumulated);

  connection delayed_call(std::function<void()> f,
                          std::chrono::nanoseconds delay);

  template <typename Rep, typename Period>
  connection delayed_call(std::function<void()> f,
                          std::chrono::duration<Rep, Period> delay);

}

#include <iscool/schedule/detail/delayed_call.tpp>
