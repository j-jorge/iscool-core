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
#include <iscool/monitoring/progress_monitor.hpp>

#include <iscool/signals/signal.impl.tpp>

iscool::monitoring::progress_monitor::progress_monitor()
  : _master(nullptr)
  , _range(1)
  , _steps(0)
  , _progress(0)
{}

iscool::monitoring::progress_monitor::progress_monitor(progress_monitor&& that)
  : _master(that._master)
  , _range(that._range)
  , _steps(0)
  , _progress(0)
{}

iscool::monitoring::progress_monitor::progress_monitor(
    progress_monitor& master, std::uint32_t range)
  : _master(&master)
  , _range(range)
  , _steps(0)
  , _progress(0)
{
  assert(_master->is_started());
  assert(_range <= _master->get_remaining_range());
}

iscool::signals::connection
iscool::monitoring::progress_monitor::connect_to_updated(
    std::function<void(float)> f) const
{
  assert(_master == nullptr);
  return _updated.connect(std::move(f));
}

void iscool::monitoring::progress_monitor::begin_monitoring(
    std::uint32_t steps)
{
  assert(_steps == 0);
  assert(steps != 0);
  assert(_progress == 0);

  _steps = steps;
}

void iscool::monitoring::progress_monitor::worked(std::uint32_t count)
{
  assert(count != 0);
  assert(count <= (1 - _progress) * _steps + 0.5);
  internal_worked(float(count) / _steps);
}

void iscool::monitoring::progress_monitor::done()
{
  if ((_progress == 1) || !is_started())
    return;

  internal_worked(1 - _progress);
}

bool iscool::monitoring::progress_monitor::is_started() const
{
  return _steps != 0;
}

void iscool::monitoring::progress_monitor::internal_worked(float count)
{
  const float new_progress(std::min(1.f, _progress + count));

  if (new_progress == 1)
    {
      _steps = 0;
      _progress = 0;
    }
  else
    _progress = new_progress;

  if (_master == nullptr)
    _updated(new_progress);
  else
    _master->internal_worked(count * _range / _master->_steps);
}

std::uint32_t iscool::monitoring::progress_monitor::get_remaining_range() const
{
  return _steps * (1 - _progress) + 0.5;
}
