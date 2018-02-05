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
#include "iscool/schedule/scaled_timer.h"

#include "gtest/gtest.h"

#include <unistd.h>

namespace detail
{
    static const std::chrono::milliseconds lower_bound_per_100_ms( 96 );
    static const std::chrono::milliseconds upper_bound_per_100_ms( 104 );
}

TEST( iscool_schedule_scaled_timer, setter )
{
    iscool::schedule::scaled_timer timer;

    EXPECT_EQ( 1.f, timer.get_scale() );

    timer.set_scale( 9 );
    EXPECT_EQ( 9.f, timer.get_scale() );
}

TEST( iscool_schedule_scaled_timer, get_duration_no_scale )
{
    iscool::schedule::scaled_timer timer;
    static constexpr useconds_t milliseconds( 1000 );

    timer.resume();
    usleep( 200 * milliseconds );
    timer.pause();

    const std::chrono::milliseconds date
        ( timer.get_duration< std::chrono::milliseconds >() );
    EXPECT_GE( date, 2 * detail::lower_bound_per_100_ms );
    EXPECT_LE( date, 2 * detail::upper_bound_per_100_ms );

    usleep( 100 * milliseconds );
    const std::chrono::milliseconds date_in_pause
        ( timer.get_duration< std::chrono::milliseconds >() );
    EXPECT_EQ( date, date_in_pause );

    timer.resume();
    usleep( 200 * milliseconds );

    timer.pause();

    const std::chrono::milliseconds date_resumed
        ( timer.get_duration< std::chrono::milliseconds >() );
    EXPECT_GE( date_resumed - date, 2 * detail::lower_bound_per_100_ms );
    EXPECT_LE( date_resumed - date, 2 * detail::upper_bound_per_100_ms );
}

TEST( iscool_schedule_scaled_timer, get_duration_doubled )
{
    iscool::schedule::scaled_timer timer;
    static constexpr useconds_t milliseconds( 1000 );

    timer.set_scale( 2 );
    timer.resume();
    usleep( 200 * milliseconds );
    timer.pause();

    const std::chrono::milliseconds date
        ( timer.get_duration< std::chrono::milliseconds >() );
    EXPECT_GE( date, 4 * detail::lower_bound_per_100_ms );
    EXPECT_LE( date, 4 * detail::upper_bound_per_100_ms );

    usleep( 100 * milliseconds );
    const std::chrono::milliseconds date_in_pause
        ( timer.get_duration< std::chrono::milliseconds >() );
    EXPECT_EQ( date, date_in_pause );

    timer.resume();
    usleep( 200 * milliseconds );

    timer.pause();

    const std::chrono::milliseconds date_resumed
        ( timer.get_duration< std::chrono::milliseconds >() );
    EXPECT_GE( date_resumed - date, 4 * detail::lower_bound_per_100_ms );
    EXPECT_LE( date_resumed - date, 4 * detail::upper_bound_per_100_ms );
}

TEST( iscool_schedule_scaled_timer, get_duration_multiple_scales )
{
    iscool::schedule::scaled_timer timer;
    static constexpr useconds_t milliseconds( 1000 );

    timer.resume();
    usleep( 200 * milliseconds );
    timer.pause();

    const std::chrono::milliseconds date_step_1
        ( timer.get_duration< std::chrono::milliseconds >() );
    EXPECT_GE( date_step_1, 2 * detail::lower_bound_per_100_ms );
    EXPECT_LE( date_step_1, 2 * detail::upper_bound_per_100_ms );

    timer.set_scale( 0.5 );

    timer.resume();
    usleep( 100 * milliseconds );
    timer.pause();

    const std::chrono::milliseconds date_step_2
        ( timer.get_duration< std::chrono::milliseconds >() );
    EXPECT_GE( date_step_2, date_step_1 + detail::lower_bound_per_100_ms / 2 );
    EXPECT_LE( date_step_2, date_step_1 + detail::upper_bound_per_100_ms / 2 );

    timer.set_scale( 2 );

    timer.resume();
    usleep( 100 * milliseconds );
    timer.pause();

    const std::chrono::milliseconds date_step_3
        ( timer.get_duration< std::chrono::milliseconds >() );
    EXPECT_GE( date_step_3, date_step_2 + 2 * detail::lower_bound_per_100_ms );
    EXPECT_LE( date_step_3, date_step_2 + 2 * detail::upper_bound_per_100_ms );
}
