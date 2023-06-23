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
#include "iscool/schedule/task.h"

#include "iscool/signals/implement_signal.h"
#include "iscool/strings/format.h"

#include <cassert>

IMPLEMENT_SIGNAL(iscool::schedule::task, complete, _complete);

constexpr std::chrono::milliseconds iscool::schedule::task::no_update_interval;

iscool::schedule::task::task(const std::string& name)
  : _profiler(name)
  , _update_count(0)
{}

iscool::schedule::task::~task()
{
  if (_profiler.started())
    end_profiler();
}

void iscool::schedule::task::complete()
{
  _profiler.append_tag("completed");
  end_profiler();
  _complete();
}

void iscool::schedule::task::append_profile_tag(const std::string& tag)
{
  _profiler.append_tag(tag);
}

void iscool::schedule::task::start()
{
  _profiler.start();
  implementation_start();
}

void iscool::schedule::task::update()
{
  ++_update_count;
  implementation_update();
}

void iscool::schedule::task::abort()
{
  _profiler.append_tag("aborted");
  implementation_abort();
  end_profiler();
}

std::chrono::milliseconds iscool::schedule::task::get_update_interval() const
{
  return implementation_get_update_interval();
}

void iscool::schedule::task::implementation_start()
{}

void iscool::schedule::task::implementation_update()
{}

void iscool::schedule::task::implementation_abort()
{}

std::chrono::milliseconds
iscool::schedule::task::implementation_get_update_interval() const
{
  return no_update_interval;
}

void iscool::schedule::task::end_profiler()
{
  assert(_profiler.started());
  if (_update_count != 0)
    _profiler.append_tag(
        iscool::strings::format("update-count=%u", _update_count));
  _profiler.end();
}
