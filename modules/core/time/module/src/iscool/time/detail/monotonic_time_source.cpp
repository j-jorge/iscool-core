#include <iscool/time/detail/monotonic_time_source.hpp>

iscool::time::time_source_delegate
    iscool::time::detail::monotonic_time_source =
        []() -> std::chrono::nanoseconds
{
  return std::chrono::steady_clock::now().time_since_epoch();
};
