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
#include "iscool/schedule/time_bounded_for_each.h"

#include "iscool/schedule/delayed_call.h"
#include "iscool/signals/implement_signal.h"
#include "iscool/time/now.h"

IMPLEMENT_SIGNAL
( iscool::schedule::time_bounded_for_each, completed, _completed );

iscool::schedule::time_bounded_for_each::time_bounded_for_each()
    : _looping( false )
{

}

iscool::schedule::time_bounded_for_each::~time_bounded_for_each() = default;

void iscool::schedule::time_bounded_for_each::abort()
{
    _loop_connection.disconnect();
    _calls.clear();
}

void iscool::schedule::time_bounded_for_each::schedule_loop()
{
    _loop_connection =
        delayed_call
        ( std::bind( &time_bounded_for_each::loop, this ),
          short_call_policy::non_cumulated );
}

void iscool::schedule::time_bounded_for_each::loop()
{
    assert( _next_index <= _calls.size() );
                
    const duration_type start( time::now< duration_type >() );

    _looping = true;

    bool limit_reached( false );
    while ( !limit_reached && ( _next_index < _calls.size() ) )
    {
        _calls[ _next_index ]();
        ++_next_index;
        limit_reached = time::now< duration_type >() - start >= _time_limit;
    }
    
    _looping = false;

    if ( _next_index < _calls.size() )
        schedule_loop();
    else
        _completed();
}
