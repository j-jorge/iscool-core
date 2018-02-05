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
#ifndef ISCOOL_SCHEDULE_TIME_BOUNDED_FOR_EACH_TPP
#define ISCOOL_SCHEDULE_TIME_BOUNDED_FOR_EACH_TPP

#include <boost/bind.hpp>

template
<
    typename Iterator,
    typename Function,
    typename Rep,
    typename Period
>
void iscool::schedule::time_bounded_for_each::operator()
( Iterator first, Iterator last, Function f,
  std::chrono::duration< Rep, Period > time_limit )
{
    assert( !_looping );

    _calls.resize( 0 );
    _calls.reserve( std::distance( first, last ) );

    for( Iterator it( first ); it != last; ++it )
        _calls.push_back( boost::bind< void >( f, *it ) );

    _next_index = 0;
    _time_limit = std::chrono::duration_cast< duration_type >( time_limit );
    schedule_loop();
}

#endif
