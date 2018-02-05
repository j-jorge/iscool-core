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
#include "iscool/signals/shared_connection_set.h"
#include "iscool/signals/signal.h"

#include "iscool/test/debug_crash.h"

#include <gtest/gtest.h>

TEST( iscool_signals_shared_connection_set, initially_empty )
{
    iscool::signals::shared_connection_set set;
    EXPECT_TRUE( set.empty() );
}

TEST( iscool_signals_shared_connection_set, clear_empty_has_no_effect )
{
    iscool::signals::shared_connection_set set;
    set.clear();
    EXPECT_TRUE( set.empty() );
}

TEST( iscool_signals_shared_connection_set, stores_disconnected_connections )
{
    iscool::signals::shared_connection_set set;
    set.insert( iscool::signals::connection() );
    EXPECT_FALSE( set.empty() );
}

TEST( iscool_signals_shared_connection_set, copy )
{
    iscool::signals::shared_connection_set set;
    set.insert( iscool::signals::connection() );
    iscool::signals::shared_connection_set copy( set );
    EXPECT_FALSE( copy.empty() );
}

TEST( iscool_signals_shared_connection_set, insert_other_set )
{
    iscool::signals::shared_connection_set set;
    set.insert( iscool::signals::connection() );
    iscool::signals::shared_connection_set copy;
    copy.insert( set );
    EXPECT_FALSE( copy.empty() );
}

TEST( iscool_signals_shared_connection_set, store_connections )
{
    iscool::signals::void_signal signal;
    iscool::signals::shared_connection_set set;
    set.insert( signal.connect( []() -> void {} ) );
    EXPECT_FALSE( signal.empty() );
}

TEST( iscool_signals_shared_connection_set, disconnect_when_cleared )
{
    iscool::signals::void_signal signal;
    iscool::signals::shared_connection_set set;
    set.insert( signal.connect( []() -> void {} ) );
    set.clear();
    EXPECT_TRUE( signal.empty() );
}

TEST( iscool_signals_shared_connection_set, clear_on_destruction )
{
    iscool::signals::void_signal signal;

    {
        iscool::signals::shared_connection_set set;
        set.insert( signal.connect( []() -> void {} ) );
    }

    EXPECT_TRUE( signal.empty() );
}

TEST( iscool_signals_shared_connection_set, debug_crash_on_duplicate )
{
    iscool::signals::void_signal signal;
    iscool::signals::connection connection( signal.connect( []() -> void {} ) );

    iscool::signals::shared_connection_set set;
    set.insert( connection );

    EXPECT_DEBUG_CRASH( set.insert( connection ) );
}
