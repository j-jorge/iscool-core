#pragma once

#include <iscool/time/detail/monotonic_time_source.hpp>

template <typename Duration>
Duration iscool::time::monotonic_now()
{
  return std::chrono::duration_cast<Duration>(
      iscool::time::detail::monotonic_time_source());
}
