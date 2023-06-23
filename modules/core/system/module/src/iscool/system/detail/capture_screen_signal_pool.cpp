/*
  Copyright 2018-present IsCool Entertainment

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#include "iscool/system/detail/capture_screen_signal_pool.h"

#include "iscool/signals/signal.impl.tpp"

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
