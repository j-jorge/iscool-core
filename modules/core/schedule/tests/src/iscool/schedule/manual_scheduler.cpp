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
#include "iscool/schedule/manual_scheduler.h"

#include "gtest/gtest.h"

TEST( iscool_schedule_manual_scheduler, update )
{
    iscool::schedule::manual_scheduler scheduler;
    auto schedule_call( scheduler.get_delayed_call_delegate() );

    bool called( false );
    auto f
        ( [ &called ]() -> void
          {
              called = true;
          } );

    schedule_call( f, std::chrono::milliseconds( 10 ) );

    scheduler.update_interval( std::chrono::milliseconds( 5 ) );
    EXPECT_FALSE( called );

    scheduler.update_interval( std::chrono::milliseconds( 5 ) );
    EXPECT_TRUE( called );

    called = false;
    scheduler.update_interval( std::chrono::milliseconds( 20 ) );
    EXPECT_FALSE( called );

    called = false;
    schedule_call( f, std::chrono::milliseconds( 0 ) );
    scheduler.update_interval( std::chrono::milliseconds( 0 ) );
    EXPECT_TRUE( called );
}

TEST( iscool_schedule_manual_scheduler, delay_in_callback )
{
    iscool::schedule::manual_scheduler scheduler;
    auto schedule_call( scheduler.get_delayed_call_delegate() );

    bool extra_called( false );
    auto extra_call
        ( [ &extra_called ]() -> void
          {
              extra_called = true;
          } );

    bool reschedule_called( false );
    auto reschedule
        ( [ &schedule_call, &reschedule_called, extra_call ]() -> void
          {
              reschedule_called = true;
              schedule_call( extra_call, std::chrono::milliseconds( 0 ) );
          } );

    schedule_call( reschedule, std::chrono::milliseconds( 0 ) );
    scheduler.update_interval( std::chrono::milliseconds( 0 ) );
    EXPECT_TRUE( reschedule_called );
    EXPECT_FALSE( extra_called );

    scheduler.update_interval( std::chrono::milliseconds( 0 ) );
    EXPECT_TRUE( reschedule_called );
}

TEST( iscool_schedule_manual_scheduler, delay_until_next_non_immediate_call )
{
    iscool::schedule::manual_scheduler scheduler;
    EXPECT_EQ
        (std::chrono::nanoseconds::zero(),
         scheduler.delay_until_next_non_immediate_call());

    auto schedule_call( scheduler.get_delayed_call_delegate() );

    int call_count = 0;
    auto call = [&call_count]() -> void
        {
            ++call_count;
        };

    schedule_call(call, std::chrono::nanoseconds::zero());
    EXPECT_EQ
        (std::chrono::nanoseconds::zero(),
         scheduler.delay_until_next_non_immediate_call());

    schedule_call(call, std::chrono::milliseconds(1));
    schedule_call(call, std::chrono::milliseconds(3));
    EXPECT_EQ
        (std::chrono::milliseconds(1),
         scheduler.delay_until_next_non_immediate_call());

    scheduler.update_interval( std::chrono::milliseconds( 1 ) );
    EXPECT_EQ(2, call_count);

    EXPECT_EQ
        (std::chrono::milliseconds(2),
         scheduler.delay_until_next_non_immediate_call());
    scheduler.update_interval( std::chrono::milliseconds( 2 ) );
    EXPECT_EQ(3, call_count);

    EXPECT_EQ
        (std::chrono::nanoseconds::zero(),
         scheduler.delay_until_next_non_immediate_call());
}
