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
#include "iscool/schedule/manual_scheduler.h"


#include <vector>

iscool::schedule::manual_scheduler::manual_scheduler()
    : _current_date(0)
{

}

iscool::schedule::delayed_call_delegate
iscool::schedule::manual_scheduler::get_delayed_call_delegate()
{
    return std::bind
        ( &manual_scheduler::schedule_call, this, std::placeholders::_1,
          std::placeholders::_2 );
}

void iscool::schedule::manual_scheduler::update_interval
( std::chrono::nanoseconds interval )
{
    std::vector< iscool::signals::void_signal_function > calls_to_do;

    {
        const std::unique_lock<std::mutex> lock(_mutex);
        _current_date += interval;

        calls_to_do.reserve(_calls.size());

        const std::vector<call>::iterator begin(_calls.begin());
        const std::vector<call>::iterator end(_calls.end());
        std::vector<call>::iterator split;

        for (split = begin; split != end; ++split)
            if (split->at_date <= _current_date)
                calls_to_do.emplace_back(std::move(split->function));
            else
                break;

        _calls.erase(begin, split);
    }

    for ( iscool::signals::void_signal_function& s : calls_to_do )
        s();
}

void
iscool::schedule::manual_scheduler::schedule_call
( iscool::signals::void_signal_function f, std::chrono::nanoseconds delay )
{
    assert( delay.count() >= 0 );

    const std::unique_lock<std::mutex> lock(_mutex);

    const std::chrono::nanoseconds at_date = _current_date + delay;
    std::vector<call>::iterator it;

    for (it = _calls.begin(); it != _calls.end(); ++it)
        if (it->at_date > at_date)
            break;

    _calls.insert(it, call{at_date, std::move(f)});
}
