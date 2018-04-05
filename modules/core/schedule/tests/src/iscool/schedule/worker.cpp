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
#include "iscool/schedule/worker.h"

#include "iscool/schedule/delayed_call.h"
#include "iscool/schedule/manual_scheduler.h"
#include "iscool/schedule/setup.h"

#include "iscool/test/no_crash.h"

#include <unistd.h>

#include "iscool/schedule/test/observable_task.h"
#include "iscool/schedule/test/task_activity_report.h"

#include <gtest/gtest.h>

class iscool_schedule_worker_test:
    public ::testing::Test
{
public:
    iscool_schedule_worker_test();
    ~iscool_schedule_worker_test();
    
    void wait( std::chrono::milliseconds delay );
    void wait( std::size_t count, std::chrono::milliseconds delay );
    
protected:
    iscool::schedule::test::task_activity_report _report;

private:
    iscool::schedule::manual_scheduler _scheduler;
};

iscool_schedule_worker_test::iscool_schedule_worker_test()
{
    iscool::schedule::initialize( _scheduler.get_delayed_call_delegate() );
}

iscool_schedule_worker_test::~iscool_schedule_worker_test()
{
    iscool::schedule::finalize();
}

void iscool_schedule_worker_test::wait( std::chrono::milliseconds delay )
{
    if ( delay != std::chrono::milliseconds::zero() )
        std::this_thread::sleep_for( delay );
    
    _scheduler.update_interval( delay );
}

void iscool_schedule_worker_test::wait
( std::size_t count, std::chrono::milliseconds delay )
{
    for ( ; count != 0; --count )
        wait( delay );
}

TEST_F( iscool_schedule_worker_test, delayed_start )
{
    std::chrono::milliseconds update_interval
        ( iscool::schedule::task::no_update_interval );
    
    const iscool::schedule::worker::handle handle
        ( iscool::schedule::worker::run
          < iscool::schedule::test::observable_task >
          ( std::ref( update_interval ), std::ref( _report ) ) );
    
    EXPECT_EQ( std::size_t( 0 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );

    wait( std::chrono::milliseconds::zero() );

    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );
}

TEST_F( iscool_schedule_worker_test, abort_when_destroyed )
{
    std::chrono::milliseconds update_interval
        ( iscool::schedule::task::no_update_interval );
    
    iscool::schedule::worker::handle handle
        ( iscool::schedule::worker::run
          < iscool::schedule::test::observable_task >
          ( std::ref( update_interval ), std::ref( _report ) ) );
    
    wait( std::chrono::milliseconds::zero() );

    handle = nullptr;
    
    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 1 ), _report.abort_calls );
}

TEST_F( iscool_schedule_worker_test, no_abort_when_destroyed_immediately )
{
    std::chrono::milliseconds update_interval
        ( iscool::schedule::task::no_update_interval );
    
    iscool::schedule::worker::handle handle
        ( iscool::schedule::worker::run
          < iscool::schedule::test::observable_task >
          ( std::ref( update_interval ), std::ref( _report ) ) );

    handle = nullptr;
    
    EXPECT_EQ( std::size_t( 0 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );
}

TEST_F( iscool_schedule_worker_test, update )
{
    std::chrono::milliseconds update_interval( 10 );
    
    const iscool::schedule::worker::handle handle
        ( iscool::schedule::worker::run
          < iscool::schedule::test::observable_task >
          ( std::ref( update_interval ), std::ref( _report ) ) );
    
    EXPECT_EQ( std::size_t( 0 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );

    wait( std::chrono::milliseconds::zero() );

    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );

    wait( std::chrono::milliseconds( 10 ) );

    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 1 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );

    wait( 2, std::chrono::milliseconds( 10 ) );

    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 3 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );

    update_interval = std::chrono::milliseconds( 2 );
    
    wait( std::chrono::milliseconds( 10 ) );

    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 4 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );
    
    wait( 5, std::chrono::milliseconds( 2 ) );

    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 9 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );

    update_interval = iscool::schedule::task::no_update_interval;

    wait( std::chrono::milliseconds( 2 ) );

    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 10 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );

    wait( 5, std::chrono::milliseconds( 2 ) );

    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 10 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );
}

TEST_F( iscool_schedule_worker_test, complete_after_start )
{
    std::chrono::milliseconds update_interval( 10 );
    
    iscool::signals::signal< void() > complete;
    const iscool::schedule::worker::handle handle
        ( iscool::schedule::worker::run
          < iscool::schedule::test::observable_task >
          ( std::ref( update_interval ), std::ref( _report ),
            std::ref( complete ) ) );
    
    wait( std::chrono::milliseconds::zero() );

    complete();

    ASSERT_NO_CRASH( wait( std::chrono::milliseconds( 10 ) ) );
}

TEST_F( iscool_schedule_worker_test, complete_when_not_updating )
{
    std::chrono::milliseconds update_interval( 10 );
    
    iscool::signals::signal< void() > complete;
    const iscool::schedule::worker::handle handle
        ( iscool::schedule::worker::run
          < iscool::schedule::test::observable_task >
          ( std::ref( update_interval ), std::ref( _report ),
            std::ref( complete ) ) );
    
    wait( std::chrono::milliseconds::zero() );

    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );

    wait( std::chrono::milliseconds( 10 ) );

    EXPECT_EQ( std::size_t( 1 ), _report.start_calls );
    EXPECT_EQ( std::size_t( 1 ), _report.update_calls );
    EXPECT_EQ( std::size_t( 0 ), _report.abort_calls );

    complete();

    ASSERT_NO_CRASH( wait( std::chrono::milliseconds( 10 ) ) );
}
