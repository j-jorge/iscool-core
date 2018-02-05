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
#include "iscool/signals/one_shot_signal.h"
#include "iscool/signals/one_shot_signal.impl.tpp"

#include <gtest/gtest.h>

TEST( iscool_signals_one_shot_signal, initially_empty )
{
    iscool::signals::one_shot_signal< void() > signal;
    EXPECT_TRUE( signal.empty() );
}

TEST( iscool_signals_one_shot_signal, connect )
{
    iscool::signals::one_shot_signal< void() > signal;

    bool called( false );
    signal.connect
        ( [ &called ]() -> void
          {
              called = true;
          } );

    EXPECT_FALSE( signal.empty() );
    
    signal();
    EXPECT_TRUE( called );
}

TEST( iscool_signals_one_shot_signal, disconnect_all_slots )
{
    iscool::signals::one_shot_signal< void() > signal;

    bool called( false );
    signal.connect
        ( [ &called ]() -> void
          {
              called = true;
          } );

    signal.disconnect_all_slots();
    signal();
    EXPECT_FALSE( called );
}

TEST( iscool_signals_one_shot_signal, call_once )
{
    iscool::signals::one_shot_signal< void() > signal;

    bool called( false );
    signal.connect
        ( [ &called ]() -> void
          {
              called = true;
          } );

    signal();
    EXPECT_TRUE( called );

    called = false;
    signal();
    EXPECT_FALSE( called );
}

TEST( iscool_signals_one_shot_signal, call_order )
{
    iscool::signals::one_shot_signal< void() > signal;

    std::size_t calls( 0 );
    std::size_t first_call( 0 );
    signal.connect
        ( [ &calls, &first_call ]() -> void
          {
              ++calls;
              first_call = calls;
          } );
    
    std::size_t second_call( 0 );
    signal.connect
        ( [ &calls, &second_call ]() -> void
          {
              ++calls;
              second_call = calls;
          } );

    signal();
    EXPECT_EQ( std::size_t( 1 ), first_call );
    EXPECT_EQ( std::size_t( 2 ), second_call );
}

TEST( iscool_signals_one_shot_signal, connect_while_triggered )
{
    iscool::signals::one_shot_signal< void() > signal;

    bool called( false );
    auto set_call
        ( [ &called ]() -> void
          {
              called = true;
          } );
    
    signal.connect
        ( [ &signal, set_call ]() -> void
          {
              signal.connect( set_call );
          } );

    signal();
    EXPECT_FALSE( called );

    signal();
    EXPECT_TRUE( called );
}

TEST( iscool_signals_one_shot_signal, argument )
{
    iscool::signals::one_shot_signal< void( int ) > signal;

    int arg( 0 );
    signal.connect
        ( [ &arg ]( int v ) -> void
          {
              arg = v;
          } );

    signal( 24 );
    EXPECT_EQ( 24, arg );
}
