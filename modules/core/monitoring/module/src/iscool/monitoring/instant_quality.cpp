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
#include "iscool/monitoring/instant_quality.h"

#include "iscool/signals/implement_signal.h"

#include <cassert>

IMPLEMENT_SIGNAL
( iscool::monitoring::instant_quality, quality_changed, _quality_changed );

iscool::monitoring::instant_quality::instant_quality( std::size_t log_length )
    : _result_log( log_length )
{
    assert( log_length != 0 );
    reset();
}

iscool::monitoring::instant_quality::~instant_quality() = default;

void iscool::monitoring::instant_quality::reset()
{
    _attempts = 0;
    _next_result_slot = 0;
    _last_quality_level = _result_log.size();
    std::fill( _result_log.begin(), _result_log.end(), 1 );
}

float iscool::monitoring::instant_quality::get_last_measure() const
{
    return float( _last_quality_level ) / _result_log.size();
}

void iscool::monitoring::instant_quality::add_attempt()
{
    ++_attempts;
}

void iscool::monitoring::instant_quality::add_success()
{
    update_quality_level( true );
}

void iscool::monitoring::instant_quality::add_failure()
{
    update_quality_level( false );
}

void
iscool::monitoring::instant_quality::update_quality_level( bool success )
{
    if ( _attempts == 0 )
        return;

    --_attempts;
    
    const std::size_t previous_quality_level( _last_quality_level );
    _last_quality_level += success - _result_log[ _next_result_slot ];

    queue_result( success );

    if ( previous_quality_level != _last_quality_level )
        _quality_changed( get_last_measure() );
}

void iscool::monitoring::instant_quality::queue_result( bool success )
{
    _result_log[ _next_result_slot ] = success;
    ++_next_result_slot;

    if ( _next_result_slot == _result_log.size() )
        _next_result_slot = 0;
}

