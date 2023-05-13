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
    : _current_date( 0 )
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
( std::chrono::milliseconds interval )
{
    _current_date += interval;

    auto bit( _calls.begin() );
    auto eit( _calls.upper_bound( _current_date.count() ) );

    std::vector< iscool::signals::void_signal_function > calls_to_do
        ( std::distance( bit, eit ) );

    std::size_t i( 0 );
    for ( auto it( bit ); it != eit; ++it, ++i )
        calls_to_do[i].swap( it->second );

    _calls.erase( bit, eit );

    for ( auto& s : calls_to_do )
        s();
}

void
iscool::schedule::manual_scheduler::schedule_call
( iscool::signals::void_signal_function f, std::chrono::milliseconds delay )
{
    assert( delay.count() >= 0 );
    _calls.insert
        ( call_map::value_type( _current_date.count() + delay.count(), f ) );
}
