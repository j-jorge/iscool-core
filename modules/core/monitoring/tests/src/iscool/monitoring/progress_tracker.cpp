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
#include "iscool/monitoring/declare_progress_tracker.h"
#include "iscool/monitoring/implement_progress_tracker.h"

#include <gtest/gtest.h>

ic_monitoring_declare_progress_tracker
( global_namespace_tracker, ( step_1 )( step_2 )( step_3 ) );

namespace dummy
{
    ic_monitoring_declare_progress_tracker
    ( in_namespace_tracker, ( step_1 )( step_2 ) );
}

ic_monitoring_implement_progress_tracker( , global_namespace_tracker )
ic_monitoring_implement_progress_tracker( dummy, in_namespace_tracker )

TEST( iscool_progress_tracker, completion )
{
    bool called( false );
    global_namespace_tracker tracker
        ( [ &called ]() -> void
          {
              called = true;
          } );

    tracker.done( global_namespace_tracker::step::step_1 );
    tracker.done( global_namespace_tracker::step::step_3 );

    EXPECT_FALSE( called );
    tracker.done( global_namespace_tracker::step::step_2 );

    EXPECT_TRUE( called );
}

TEST( iscool_progress_tracker, double_completion_failure )
{
    bool called( false );
    dummy::in_namespace_tracker tracker
        ( [ &called ]() -> void
          {
              called = true;
          } );

    tracker.done( dummy::in_namespace_tracker::step::step_2 );
    ASSERT_DEATH
        ( tracker.done( dummy::in_namespace_tracker::step::step_2 ), "" );
}

TEST( iscool_progress_tracker, reset )
{
    int called( 0 );
    global_namespace_tracker tracker
        ( [ &called ]() -> void
          {
              called++;
          } );

    tracker.done( global_namespace_tracker::step::step_1 );
    tracker.done( global_namespace_tracker::step::step_3 );

    EXPECT_EQ( 0, called );
    tracker.done( global_namespace_tracker::step::step_2 );

    EXPECT_EQ( 1, called );
    tracker.reset();

    EXPECT_EQ( 1, called );

    tracker.done( global_namespace_tracker::step::step_1 );
    tracker.done( global_namespace_tracker::step::step_3 );

    EXPECT_EQ( 1, called );
    tracker.done( global_namespace_tracker::step::step_2 );

    EXPECT_EQ( 2, called );
    
    int second_called( 0 );
    tracker.reset
        ( [ &second_called ]() -> void
          {
              second_called++;
          } );

    EXPECT_EQ( 2, called );
    EXPECT_EQ( 0, second_called );

    tracker.done( global_namespace_tracker::step::step_1 );
    tracker.done( global_namespace_tracker::step::step_3 );

    EXPECT_EQ( 2, called );
    EXPECT_EQ( 0, second_called );
    tracker.done( global_namespace_tracker::step::step_2 );

    EXPECT_EQ( 2, called );
    EXPECT_EQ( 1, second_called );
}
