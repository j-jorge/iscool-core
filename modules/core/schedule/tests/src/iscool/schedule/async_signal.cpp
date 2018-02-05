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
#include "iscool/schedule/async_signal.h"
#include "iscool/schedule/manual_scheduler.h"
#include "iscool/schedule/setup.h"
#include "iscool/signals/implement_signal.h"

#include "gtest/gtest.h"

class iscool_schedule_async_signal_macro_void_test
{
    DECLARE_ASYNC_VOID_SIGNAL( test, _signal );

public:
    void trigger();
};

IMPLEMENT_SIGNAL( iscool_schedule_async_signal_macro_void_test, test, _signal );

void iscool_schedule_async_signal_macro_void_test::trigger()
{
    _signal();
}

TEST( iscool_schedule_async_signal, is_delayed )
{
    iscool::schedule::manual_scheduler scheduler;
    iscool::schedule::initialize( scheduler.get_delayed_call_delegate() );
    
    bool called( false );
    iscool_schedule_async_signal_macro_void_test test;
    test.connect_to_test
        ( [ &called ]() -> void
          {
              called = true;
          } );
    
    test.trigger();
    EXPECT_FALSE( called );

    scheduler.update_interval( std::chrono::milliseconds::zero() );
    EXPECT_TRUE( called );

    iscool::schedule::finalize();
}

TEST( iscool_schedule_async_signal, connection )
{
    iscool::schedule::manual_scheduler scheduler;
    iscool::schedule::initialize( scheduler.get_delayed_call_delegate() );
    
    bool called( false );
    iscool_schedule_async_signal_macro_void_test test;
    iscool::signals::connection c
        ( test.connect_to_test
          ( [ &called ]() -> void
            {
                called = true;
            } ) );
          
    test.trigger();
    EXPECT_FALSE( called );
    c.disconnect();
    
    scheduler.update_interval( std::chrono::milliseconds::zero() );
    EXPECT_FALSE( called );

    iscool::schedule::finalize();
}

TEST( iscool_schedule_async_signal, multiple_calls )
{
    iscool::schedule::manual_scheduler scheduler;
    iscool::schedule::initialize( scheduler.get_delayed_call_delegate() );
    
    std::size_t calls( 0 );
    iscool_schedule_async_signal_macro_void_test test;
    iscool::signals::connection c
        ( test.connect_to_test
          ( [ &calls ]() -> void
            {
                ++calls;
            } ) );
          
    test.trigger();
    test.trigger();
    EXPECT_EQ( std::size_t( 0 ), calls );
    
    scheduler.update_interval( std::chrono::milliseconds::zero() );
    EXPECT_EQ( std::size_t( 2 ), calls );

    iscool::schedule::finalize();
}

class iscool_schedule_async_signal_macro_arguments_test
{
    DECLARE_ASYNC_SIGNAL( void( int, std::string ), test, _signal );

public:
    void trigger( int i, std::string s );
};

IMPLEMENT_SIGNAL
( iscool_schedule_async_signal_macro_arguments_test, test, _signal );

void iscool_schedule_async_signal_macro_arguments_test::trigger
( int i, std::string s )
{
    _signal( i, s );
}

TEST( iscool_schedule_async_signal, arguments )
{
    iscool::schedule::manual_scheduler scheduler;
    iscool::schedule::initialize( scheduler.get_delayed_call_delegate() );
    
    iscool_schedule_async_signal_macro_arguments_test test;
    int int_value( 0 );
    std::string string_value;
    
    test.connect_to_test
        ( [ &int_value, &string_value ]( int i, std::string s ) -> void
          {
              int_value = i;
              string_value = s;
          } );
          
    test.trigger( 24, "yep" );
    EXPECT_EQ( 0, int_value );
    EXPECT_TRUE( string_value.empty() );
    
    scheduler.update_interval( std::chrono::milliseconds::zero() );
    EXPECT_EQ( 24, int_value );
    EXPECT_EQ( "yep", string_value );

    iscool::schedule::finalize();
}
