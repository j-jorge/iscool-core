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
#ifndef ISCOOL_SCHEDULE_CLOCK_TPP
#define ISCOOL_SCHEDULE_CLOCK_TPP

template<typename Tick>
iscool::signals::connection
iscool::schedule::clock< Tick >::connect_to_tick
( iscool::signals::void_signal_function f )
{
    return _tick.connect( f );
}

template<typename Tick>
Tick iscool::schedule::clock<Tick>::get_date() const
{
    return implementation_get_date();
}

template<typename Tick>
void iscool::schedule::clock<Tick>::trigger_tick_signal() const
{
    _tick();
}

#endif
