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
#include "iscool/schedule/scaled_timer.h"

iscool::schedule::scaled_timer::scaled_timer()
  : _scale(1)
{
  reset();
}

void iscool::schedule::scaled_timer::set_scale(float scale)
{
  const duration now(_timer.get_duration<duration>());

  _scaled_reference +=
      duration(duration::rep((now - _real_reference).count() * _scale));
  _real_reference = now;

  _scale = scale;
}

float iscool::schedule::scaled_timer::get_scale() const
{
  return _scale;
}

void iscool::schedule::scaled_timer::reset()
{
  _timer.reset();

  _real_reference = _timer.get_duration<duration>();
  _scaled_reference = duration::zero();
}

void iscool::schedule::scaled_timer::pause()
{
  _timer.pause();
}

void iscool::schedule::scaled_timer::resume()
{
  _timer.resume();
}
