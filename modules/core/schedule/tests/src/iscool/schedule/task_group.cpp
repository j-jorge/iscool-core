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
#include "iscool/schedule/delayed_call.h"
#include "iscool/schedule/manual_scheduler.h"
#include "iscool/schedule/setup.h"
#include "iscool/schedule/task_group.h"
#include "iscool/schedule/task_group.impl.tpp"

#include <thread>

#include "iscool/schedule/test/observable_task.h"
#include "iscool/schedule/test/task_activity_report.h"

#include <gtest/gtest.h>

class iscool_schedule_task_group_test:
    public ::testing::Test
{
public:
    iscool_schedule_task_group_test();
    ~iscool_schedule_task_group_test();
    
    void wait( std::chrono::milliseconds delay );
    
private:
    iscool::schedule::manual_scheduler _scheduler;
};

iscool_schedule_task_group_test::iscool_schedule_task_group_test()
{
    iscool::schedule::initialize( _scheduler.get_delayed_call_delegate() );
}

iscool_schedule_task_group_test::~iscool_schedule_task_group_test()
{
    iscool::schedule::finalize();
}

void iscool_schedule_task_group_test::wait( std::chrono::milliseconds delay )
{
    if ( delay != std::chrono::milliseconds::zero() )
        std::this_thread::sleep_for( delay );
    
    _scheduler.update_interval( delay );
}

TEST_F( iscool_schedule_task_group_test, single_task )
{
    std::chrono::milliseconds update_interval( 10 );
    iscool::schedule::test::task_activity_report report;
    iscool::signals::signal< void() > complete;

    iscool::schedule::task_group group;
    group.run< iscool::schedule::test::observable_task >
        ( std::ref( update_interval ), std::ref( report ),
          std::ref( complete ) );
    
    EXPECT_EQ( std::size_t( 0 ), report.start_calls );
    EXPECT_EQ( std::size_t( 0 ), report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report.abort_calls );

    wait( update_interval );

    EXPECT_EQ( std::size_t( 1 ), report.start_calls );
    EXPECT_EQ( std::size_t( 0 ), report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report.abort_calls );

    wait( update_interval );

    EXPECT_EQ( std::size_t( 1 ), report.start_calls );
    EXPECT_EQ( std::size_t( 1 ), report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report.abort_calls );

    update_interval = std::chrono::milliseconds( 20 );
    wait( update_interval );

    EXPECT_EQ( std::size_t( 1 ), report.start_calls );
    EXPECT_EQ( std::size_t( 2 ), report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report.abort_calls );

    wait( std::chrono::milliseconds( 10 ) );

    EXPECT_EQ( std::size_t( 1 ), report.start_calls );
    EXPECT_EQ( std::size_t( 2 ), report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report.abort_calls );

    wait( std::chrono::milliseconds( 10 ) );

    EXPECT_EQ( std::size_t( 1 ), report.start_calls );
    EXPECT_EQ( std::size_t( 3 ), report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report.abort_calls );

    complete();
    wait( std::chrono::milliseconds( 50 ) );

    EXPECT_EQ( std::size_t( 1 ), report.start_calls );
    EXPECT_EQ( std::size_t( 3 ), report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report.abort_calls );
}


TEST_F( iscool_schedule_task_group_test, multiple_tasks )
{
    std::chrono::milliseconds update_interval_1( 10 );
    iscool::schedule::test::task_activity_report report_1;
    iscool::signals::signal< void() > complete_1;

    std::chrono::milliseconds update_interval_2( 20 );
    iscool::schedule::test::task_activity_report report_2;
    iscool::signals::signal< void() > complete_2;

    std::chrono::milliseconds update_interval_3( 10 );
    iscool::schedule::test::task_activity_report report_3;
    iscool::signals::signal< void() > complete_3;

    iscool::schedule::task_group group;
    group.run< iscool::schedule::test::observable_task >
        ( std::ref( update_interval_1 ), std::ref( report_1 ),
          std::ref( complete_1 ) );
    group.run< iscool::schedule::test::observable_task >
        ( std::ref( update_interval_2 ), std::ref( report_2 ),
          std::ref( complete_2 ) );
    group.run< iscool::schedule::test::observable_task >
        ( std::ref( update_interval_3 ), std::ref( report_3 ),
          std::ref( complete_3 ) );
    
    wait( std::chrono::milliseconds( 10 ) );

    EXPECT_EQ( std::size_t( 1 ), report_1.start_calls );
    EXPECT_EQ( std::size_t( 0 ), report_1.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_1.abort_calls );

    EXPECT_EQ( std::size_t( 1 ), report_2.start_calls );
    EXPECT_EQ( std::size_t( 0 ), report_2.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_2.abort_calls );

    EXPECT_EQ( std::size_t( 1 ), report_3.start_calls );
    EXPECT_EQ( std::size_t( 0 ), report_3.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_3.abort_calls );

    wait( std::chrono::milliseconds( 10 ) );

    EXPECT_EQ( std::size_t( 1 ), report_1.start_calls );
    EXPECT_EQ( std::size_t( 1 ), report_1.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_1.abort_calls );

    EXPECT_EQ( std::size_t( 1 ), report_2.start_calls );
    EXPECT_EQ( std::size_t( 0 ), report_2.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_2.abort_calls );

    EXPECT_EQ( std::size_t( 1 ), report_3.start_calls );
    EXPECT_EQ( std::size_t( 1 ), report_3.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_3.abort_calls );

    wait( std::chrono::milliseconds( 10 ) );

    EXPECT_EQ( std::size_t( 1 ), report_1.start_calls );
    EXPECT_EQ( std::size_t( 2 ), report_1.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_1.abort_calls );

    EXPECT_EQ( std::size_t( 1 ), report_2.start_calls );
    EXPECT_EQ( std::size_t( 1 ), report_2.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_2.abort_calls );

    EXPECT_EQ( std::size_t( 1 ), report_3.start_calls );
    EXPECT_EQ( std::size_t( 2 ), report_3.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_3.abort_calls );

    complete_1();

    wait( std::chrono::milliseconds( 10 ) );
    wait( std::chrono::milliseconds( 10 ) );

    EXPECT_EQ( std::size_t( 1 ), report_1.start_calls );
    EXPECT_EQ( std::size_t( 2 ), report_1.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_1.abort_calls );

    EXPECT_EQ( std::size_t( 1 ), report_2.start_calls );
    EXPECT_EQ( std::size_t( 2 ), report_2.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_2.abort_calls );

    EXPECT_EQ( std::size_t( 1 ), report_3.start_calls );
    EXPECT_EQ( std::size_t( 4 ), report_3.update_calls );
    EXPECT_EQ( std::size_t( 0 ), report_3.abort_calls );

}

TEST_F( iscool_schedule_task_group_test, abort_on_destroy )
{
    std::chrono::milliseconds update_interval_1( 10 );
    iscool::schedule::test::task_activity_report report_1;
    iscool::signals::signal< void() > complete_1;

    std::chrono::milliseconds update_interval_2( 20 );
    iscool::schedule::test::task_activity_report report_2;
    iscool::signals::signal< void() > complete_2;

    std::chrono::milliseconds update_interval_3( 10 );
    iscool::schedule::test::task_activity_report report_3;
    iscool::signals::signal< void() > complete_3;

    {
        iscool::schedule::task_group group;
        group.run< iscool::schedule::test::observable_task >
            ( std::ref( update_interval_1 ), std::ref( report_1 ),
              std::ref( complete_1 ) );
        group.run< iscool::schedule::test::observable_task >
            ( std::ref( update_interval_2 ), std::ref( report_2 ),
              std::ref( complete_2 ) );
        group.run< iscool::schedule::test::observable_task >
            ( std::ref( update_interval_3 ), std::ref( report_3 ),
              std::ref( complete_3 ) );
    
        wait( std::chrono::milliseconds( 10 ) );

        EXPECT_EQ( std::size_t( 1 ), report_1.start_calls );
        EXPECT_EQ( std::size_t( 0 ), report_1.update_calls );
        EXPECT_EQ( std::size_t( 0 ), report_1.abort_calls );

        EXPECT_EQ( std::size_t( 1 ), report_2.start_calls );
        EXPECT_EQ( std::size_t( 0 ), report_2.update_calls );
        EXPECT_EQ( std::size_t( 0 ), report_2.abort_calls );

        EXPECT_EQ( std::size_t( 1 ), report_3.start_calls );
        EXPECT_EQ( std::size_t( 0 ), report_3.update_calls );
        EXPECT_EQ( std::size_t( 0 ), report_3.abort_calls );

        wait( std::chrono::milliseconds( 10 ) );

        EXPECT_EQ( std::size_t( 1 ), report_1.start_calls );
        EXPECT_EQ( std::size_t( 1 ), report_1.update_calls );
        EXPECT_EQ( std::size_t( 0 ), report_1.abort_calls );

        EXPECT_EQ( std::size_t( 1 ), report_2.start_calls );
        EXPECT_EQ( std::size_t( 0 ), report_2.update_calls );
        EXPECT_EQ( std::size_t( 0 ), report_2.abort_calls );

        EXPECT_EQ( std::size_t( 1 ), report_3.start_calls );
        EXPECT_EQ( std::size_t( 1 ), report_3.update_calls );
        EXPECT_EQ( std::size_t( 0 ), report_3.abort_calls );
    }

    EXPECT_EQ( std::size_t( 1 ), report_1.start_calls );
    EXPECT_EQ( std::size_t( 1 ), report_1.update_calls );
    EXPECT_EQ( std::size_t( 1 ), report_1.abort_calls );

    EXPECT_EQ( std::size_t( 1 ), report_2.start_calls );
    EXPECT_EQ( std::size_t( 0 ), report_2.update_calls );
    EXPECT_EQ( std::size_t( 1 ), report_2.abort_calls );

    EXPECT_EQ( std::size_t( 1 ), report_3.start_calls );
    EXPECT_EQ( std::size_t( 1 ), report_3.update_calls );
    EXPECT_EQ( std::size_t( 1 ), report_3.abort_calls );
    
}
