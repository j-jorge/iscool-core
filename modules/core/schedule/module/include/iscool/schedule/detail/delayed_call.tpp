// SPDX-License-Identifier: Apache-2.0
#pragma once

template <typename Rep, typename Period>
iscool::schedule::connection
iscool::schedule::delayed_call(std::function<void()> f,
                               std::chrono::duration<Rep, Period> delay)
{
  return delayed_call(
      std::move(f),
      std::chrono::duration_cast<std::chrono::nanoseconds>(delay));
}
