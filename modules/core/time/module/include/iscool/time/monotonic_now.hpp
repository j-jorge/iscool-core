#pragma once

namespace iscool
{
  namespace time
  {
    template <typename Duration>
    Duration monotonic_now();
  }
}

#include <iscool/time/detail/monotonic_now.tpp>
