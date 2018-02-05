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
#include "iscool/signals/shared_connection.h"
#include "iscool/signals/signal.h"

#include <gtest/gtest.h>

TEST( iscool_signals_shared_connection, default_initially_disconnected )
{
    iscool::signals::shared_connection c;
    EXPECT_FALSE( c.connected() );
}

TEST( iscool_signals_shared_connection,
      initially_disconnected_from_disconnected_source )
{
    iscool::signals::connection c;
    iscool::signals::shared_connection shared_disconnected( c );
    EXPECT_FALSE( c.connected() );
}

TEST( iscool_signals_shared_connection,
      initially_connected_from_connected_source )
{
    iscool::signals::void_signal signal;
    iscool::signals::shared_connection c( signal.connect( []() -> void {} ) );
    EXPECT_TRUE( c.connected() );
}

TEST( iscool_signals_shared_connection, disconnect_disconnected_has_no_effect )
{
    iscool::signals::shared_connection c;
    c.disconnect();
    EXPECT_FALSE( c.connected() );
}

TEST( iscool_signals_shared_connection, disconnect )
{
    iscool::signals::void_signal signal;
    iscool::signals::shared_connection c( signal.connect( []() -> void {} ) );
    c.disconnect();
    EXPECT_FALSE( c.connected() );
}

TEST( iscool_signals_shared_connection, disconnect_affects_origin )
{
    iscool::signals::void_signal signal;
    iscool::signals::connection origin( signal.connect( []() -> void {} ) );
    iscool::signals::shared_connection c( origin );
    c.disconnect();
    EXPECT_FALSE( origin.connected() );
}

TEST( iscool_signals_shared_connection, equals_self_empty )
{
    iscool::signals::shared_connection c;
    EXPECT_EQ( c, c );
}

TEST( iscool_signals_shared_connection, equals_other_empty )
{
    iscool::signals::shared_connection c1;
    iscool::signals::shared_connection c2;
    EXPECT_EQ( c1, c2 );
}

TEST( iscool_signals_shared_connection,
      equals_initialized_with_same_empty_connection )
{
    iscool::signals::connection c;
    iscool::signals::shared_connection c1( c );
    iscool::signals::shared_connection c2( c );
    EXPECT_EQ( c1, c2 );
}

TEST( iscool_signals_shared_connection,
      equals_initialized_with_same_non_empty_connection )
{
    iscool::signals::void_signal signal;
    iscool::signals::connection origin( signal.connect( []() -> void {} ) );
    iscool::signals::shared_connection c1( origin );
    iscool::signals::shared_connection c2( origin );
    EXPECT_EQ( c1, c2 );
}

TEST( iscool_signals_shared_connection, copy_is_equal )
{
    iscool::signals::void_signal signal;
    iscool::signals::connection origin( signal.connect( []() -> void {} ) );
    iscool::signals::shared_connection c1( origin );
    iscool::signals::shared_connection c2( c1 );
    EXPECT_EQ( c1, c2 );
}

TEST( iscool_signals_shared_connection, empty_is_not_equal_to_non_empty )
{
    iscool::signals::void_signal signal;
    iscool::signals::connection origin( signal.connect( []() -> void {} ) );
    iscool::signals::shared_connection c1( origin );
    iscool::signals::shared_connection c2;
    EXPECT_NE( c1, c2 );
}

TEST( iscool_signals_shared_connection,
      not_equal_different_signals_connections )
{
    iscool::signals::void_signal first_signal;
    iscool::signals::shared_connection c1
        ( first_signal.connect( []() -> void {} ) );

    iscool::signals::void_signal second_signal;
    iscool::signals::shared_connection c2
        ( second_signal.connect( []() -> void {} ) );

    EXPECT_NE( c1, c2 );
}

TEST( iscool_signals_shared_connection, disconnect_all_copies )
{
    iscool::signals::void_signal signal;
    iscool::signals::connection origin( signal.connect( []() -> void {} ) );
    iscool::signals::shared_connection c1( origin );
    iscool::signals::shared_connection c2( c1 );
    c2.disconnect();
    EXPECT_FALSE( c1.connected() );
}

TEST( iscool_signals_shared_connection, leaving_scope_disconnects )
{
    iscool::signals::void_signal signal;

    {
        iscool::signals::shared_connection c1
            ( signal.connect( []() -> void {} ) );
        EXPECT_FALSE( signal.empty() );
    }

    EXPECT_TRUE( signal.empty() );
}
