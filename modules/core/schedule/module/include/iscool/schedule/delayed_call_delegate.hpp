// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <chrono>
#include <functional>

namespace iscool
{
  namespace schedule
  {
    typedef std::function<void(std::function<void()>,
                               std::chrono::nanoseconds)>
        delayed_call_delegate;
  }
}
