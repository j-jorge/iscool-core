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
#include "iscool/signals/signal.h"

#include "iscool/signals/signal.impl.tpp"

#include <gtest/gtest.h>

TEST( iscool_signals_connection, initially_disconnected )
{
    iscool::signals::connection connection;
    EXPECT_FALSE( connection.connected() );
}

TEST( iscool_signals_connection, connected )
{
    iscool::signals::signal< void() > signal;

    iscool::signals::connection connection
        ( signal.connect( []() -> void {} ) );
          
    EXPECT_TRUE( connection.connected() );
}

TEST( iscool_signals_connection, disconnect )
{
    iscool::signals::signal< void() > signal;

    bool called( false );
    
    iscool::signals::connection connection
        ( signal.connect
          ( [ &called ]() -> void
            {
                called = true;
            } ) );

    connection.disconnect();
    EXPECT_FALSE( connection.connected() );

    signal();
    EXPECT_FALSE( called );
}

TEST( iscool_signals_connection, disconnect_in_callback )
{
    iscool::signals::signal< void() > signal;

    iscool::signals::connection connection;

    signal.connect
        ( [ &connection ]() -> void
          {
              connection.disconnect();
          } );
    
    bool called( false );

    connection =
        signal.connect
        ( [ &called ]() -> void
          {
              called = true;
          } );

    signal();
    EXPECT_FALSE( called );
}

TEST( iscool_signals_connection, equality )
{
    iscool::signals::signal< void() > signal;

    iscool::signals::connection assigned;
    iscool::signals::connection connection
        ( signal.connect( []() -> void {} ) );
    iscool::signals::connection copy( connection );

    assigned = connection;
          
    EXPECT_EQ( assigned, connection );
    EXPECT_EQ( copy, connection );
}

TEST( iscool_signals_connection, disconnect_copy )
{
    iscool::signals::signal< void() > signal;

    const iscool::signals::connection connection
        ( signal.connect( []() -> void {} ) );
    iscool::signals::connection copy( connection );
    
    copy.disconnect();
    EXPECT_FALSE( connection.connected() );
}

TEST( iscool_signals_connection, different_from_different_callbacks )
{
    iscool::signals::signal< void() > signal;

    const iscool::signals::connection connection_1
        ( signal.connect( []() -> void {} ) );
    const iscool::signals::connection connection_2
        ( signal.connect( []() -> void {} ) );

    EXPECT_NE( connection_1, connection_2 );
}

TEST( iscool_signals_connection, different_from_different_signals )
{
    iscool::signals::signal< void() > signal_1;
    const iscool::signals::connection connection_1
        ( signal_1.connect( []() -> void {} ) );

    iscool::signals::signal< void() > signal_2;
    const iscool::signals::connection connection_2
        ( signal_2.connect( []() -> void {} ) );

    EXPECT_NE( connection_1, connection_2 );
}
