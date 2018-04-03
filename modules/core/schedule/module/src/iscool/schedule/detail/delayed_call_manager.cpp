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
#include "iscool/schedule/detail/delayed_call_manager.h"

#include "iscool/time/now.h"

#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/warning.h"
#include "iscool/schedule/detail/call_later.h"
#include "iscool/signals/signal.impl.tpp"

#include <boost/bind.hpp>

iscool::schedule::detail::delayed_call_manager::delayed_call_manager
( std::size_t pool_size )
    : _short_call_cumulated( "delayed_call_manager::short_call_cumulated" ),
      _short_call_non_cumulated
      ( "delayed_call_manager::short_call_non_cumulated" ),
      _pool( pool_size ),
      _client_guard( false ),
      _in_cumulated_loop( false )
{

}

iscool::signals::connection
iscool::schedule::detail::delayed_call_manager::schedule_call
( iscool::signals::void_signal_function f, duration delay )
{
    assert( delay.count() > 0 );
    return schedule_delayed( f, delay );
}

iscool::signals::connection
iscool::schedule::detail::delayed_call_manager::schedule_call
( iscool::signals::void_signal_function f, short_call_policy policy )
{
    if ( policy == short_call_policy::cumulated )
        return schedule_cumulated( f );

    assert( policy == short_call_policy::non_cumulated );
    return schedule_non_cumulated( f );
}

void iscool::schedule::detail::delayed_call_manager::clear()
{
    std::unique_lock< std::recursive_mutex > lock( _mutex );

    _short_call_cumulated.disconnect_all_slots();
    _short_call_non_cumulated.disconnect_all_slots();
    _pool.clear();
}

iscool::signals::connection
iscool::schedule::detail::delayed_call_manager::schedule_cumulated
( iscool::signals::void_signal_function f )
{
    std::unique_lock< std::recursive_mutex > lock( _mutex );

    if ( !_in_cumulated_loop && _short_call_cumulated.empty() )
        schedule_client_cumulated();

    return _short_call_cumulated.connect( f );
}

iscool::signals::connection
iscool::schedule::detail::delayed_call_manager::schedule_non_cumulated
( iscool::signals::void_signal_function f )
{
    std::unique_lock< std::recursive_mutex > lock( _mutex );

    if ( _short_call_non_cumulated.empty() )
        schedule_client_non_cumulated();

    return _short_call_non_cumulated.connect( f );
}

iscool::signals::connection
iscool::schedule::detail::delayed_call_manager::schedule_delayed
( iscool::signals::void_signal_function f, duration delay )
{
    std::unique_lock< std::recursive_mutex > lock( _mutex );

    assert( delay.count() > 0 );

    const auto slot( _pool.pick_available() );
    const iscool::signals::connection result = slot.value.connect( f );

    schedule_client( slot.id, delay );

    return result;
}

void iscool::schedule::detail::delayed_call_manager::schedule_client
( std::size_t id, duration delay )
{
    assert( !detail::call_later.empty() );

    detail::call_later
        ( boost::bind
          ( &delayed_call_manager::trigger, this,
            id, time::now< duration >() + delay ),
          delay );
}

void iscool::schedule::detail::delayed_call_manager::schedule_client_cumulated()
{
    assert( !_client_guard );
    _client_guard = true;

    assert( !detail::call_later.empty() );

    detail::call_later
        ( boost::bind( &delayed_call_manager::trigger_cumulated, this ),
          duration::zero() );

    _client_guard = false;
}

void
iscool::schedule::detail::delayed_call_manager::schedule_client_non_cumulated()
{
    assert( _short_call_non_cumulated.empty() );
    assert( !_client_guard );
    _client_guard = true;

    assert( !detail::call_later.empty() );

    detail::call_later
        ( boost::bind
          ( &delayed_call_manager::trigger_non_cumulated, this ),
          duration::zero() );

    _client_guard = false;
}

void iscool::schedule::detail::delayed_call_manager::trigger
( std::size_t id, duration expected_date )
{
    const duration now( time::now< duration >() );

    if ( expected_date > now )
    {
        const duration remaining( expected_date - now );
        schedule_client( id, remaining );
    }
    else
    {
        iscool::signals::void_signal calls;

        {
            std::unique_lock< std::recursive_mutex > lock( _mutex );
            calls.swap( _pool.get( id ) );
            _pool.release( id );
        }

        calls();
        trigger_cumulated();
    }
}

void iscool::schedule::detail::delayed_call_manager::trigger_cumulated()
{
    _mutex.lock();

    assert( !_client_guard );
    assert( !_in_cumulated_loop );

    _in_cumulated_loop = true;

    std::size_t limit( 10 );

    do
    {
        --limit;

        iscool::signals::void_signal calls;
        calls.swap( _short_call_cumulated );

        _mutex.unlock();
        calls();
        _mutex.lock();
    }
    while( ( limit != 0 ) && !_short_call_cumulated.empty() );

    _in_cumulated_loop = false;

    if ( !_short_call_cumulated.empty() )
    {
        ic_causeless_log
            ( iscool::log::nature::warning(), "Scheduler",
              "Too many recursively cumulated calls." );

        schedule_client_cumulated();
    }

    _mutex.unlock();
}

void iscool::schedule::detail::delayed_call_manager::trigger_non_cumulated()
{
    iscool::signals::void_signal calls;

    {
        std::unique_lock< std::recursive_mutex > lock( _mutex );
        assert( !_client_guard );
        calls.swap( _short_call_non_cumulated );
    }
    
    calls();
}
