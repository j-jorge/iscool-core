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
#include "iscool/system/application_event_source.h"

#include "gtest/gtest.h"

TEST( iscool_system_application_event_source, enter_background )
{
    bool called( false );
    const auto enter_background
        ( [ &called ]() -> void
          {
              called = true;
          } );

    const iscool::system::application_event_source source{};
    
    iscool::signals::connection connection
        ( source.connect_to_enter_background( enter_background ) );

    EXPECT_TRUE( connection.connected() );
    EXPECT_FALSE( called );

    source.dispatch_enter_background();
    EXPECT_TRUE( called );

    called = false;
    source.dispatch_enter_foreground();
    EXPECT_FALSE( called );

    called = false;
    connection.disconnect();
    source.dispatch_enter_background();
    EXPECT_FALSE( called );
}

TEST( iscool_system_application_event_source, enter_foreground )
{
    bool called( false );
    const auto enter_foreground
        ( [ &called ]() -> void
          {
              called = true;
          } );

    const iscool::system::application_event_source source{};
    
    iscool::signals::connection connection
        ( source.connect_to_enter_foreground( enter_foreground ) );

    EXPECT_TRUE( connection.connected() );
    EXPECT_FALSE( called );

    source.dispatch_enter_foreground();
    EXPECT_TRUE( called );

    called = false;
    source.dispatch_enter_background();
    EXPECT_FALSE( called );

    called = false;
    connection.disconnect();
    source.dispatch_enter_foreground();
    EXPECT_FALSE( called );
}
