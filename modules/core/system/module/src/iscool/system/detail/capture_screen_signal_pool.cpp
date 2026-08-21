// SPDX-License-Identifier: Apache-2.0
#include <iscool/system/detail/capture_screen_signal_pool.hpp>

#include <iscool/memory/dynamic_pool.impl.hpp>
#include <iscool/signals/signal.impl.tpp>

iscool::system::detail::capture_screen_signal_pool::capture_screen_signal_pool(
    std::size_t size)
  : _pool(size)
{}

iscool::system::detail::capture_screen_signal_pool::slot
iscool::system::detail::capture_screen_signal_pool::pick_available_signal()
{
  return _pool.pick_available();
}

void iscool::system::detail::capture_screen_signal_pool::process_capture(
    std::size_t signal_index, const std::string& path)
{
  _pool.get(signal_index)(path);
  _pool.release(signal_index);
}
