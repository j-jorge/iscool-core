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
#include "iscool/monitoring/implement_state_monitor.h"

#include "iscool/test/debug_crash.h"

#include <gtest/gtest.h>

TEST(iscool_monitoring_state_monitor, simple_initial_state)
{
  ic_inline_state_monitor(monitor, begin, ((begin)()));

  EXPECT_TRUE(monitor->is_begin_state());
}

TEST(iscool_monitoring_state_monitor, initial_state_with_multiple_state)
{
  ic_inline_state_monitor(monitor, begin,
                          ((end)())((state1)((end)))((begin)((state1))));

  EXPECT_TRUE(monitor->is_begin_state());
}

TEST(iscool_monitoring_state_monitor, simple_set_state)
{
  ic_inline_state_monitor(monitor, begin, ((begin)((end)))((end)()));

  EXPECT_TRUE(monitor->is_begin_state());

  monitor->set_end_state();
  EXPECT_TRUE(monitor->is_end_state());
}

TEST(iscool_monitoring_state_monitor, invalid_simple_set_state)
{
  ic_inline_state_monitor(monitor, begin, ((begin)((end)))((end)()));

  EXPECT_TRUE(monitor->is_begin_state());
  EXPECT_DEBUG_CRASH(monitor->set_begin_state());

  monitor->set_end_state();

  EXPECT_TRUE(monitor->is_end_state());
  EXPECT_DEBUG_CRASH(monitor->set_begin_state());
  EXPECT_DEBUG_CRASH(monitor->set_end_state());
}

TEST(iscool_monitoring_state_monitor, multiple_set_state)
{
  ic_inline_state_monitor(
      monitor, begin,
      ((begin)((first)))((first)((second)(third)))((second)((third)(first)))(
          (third)((second)(end)))((end)()));

  EXPECT_TRUE(monitor->is_begin_state());
  EXPECT_FALSE(monitor->is_first_state());
  EXPECT_FALSE(monitor->is_second_state());
  EXPECT_FALSE(monitor->is_third_state());
  EXPECT_FALSE(monitor->is_end_state());

  EXPECT_DEBUG_CRASH(monitor->set_begin_state());
  EXPECT_DEBUG_CRASH(monitor->set_second_state());
  EXPECT_DEBUG_CRASH(monitor->set_third_state());
  EXPECT_DEBUG_CRASH(monitor->set_end_state());

  monitor->set_first_state();

  EXPECT_FALSE(monitor->is_begin_state());
  EXPECT_TRUE(monitor->is_first_state());
  EXPECT_FALSE(monitor->is_second_state());
  EXPECT_FALSE(monitor->is_third_state());
  EXPECT_FALSE(monitor->is_end_state());

  EXPECT_DEBUG_CRASH(monitor->set_begin_state());
  EXPECT_DEBUG_CRASH(monitor->set_end_state());
  EXPECT_DEBUG_CRASH(monitor->set_first_state());

  monitor->set_second_state();

  EXPECT_FALSE(monitor->is_begin_state());
  EXPECT_FALSE(monitor->is_first_state());
  EXPECT_TRUE(monitor->is_second_state());
  EXPECT_FALSE(monitor->is_third_state());
  EXPECT_FALSE(monitor->is_end_state());

  EXPECT_DEBUG_CRASH(monitor->set_begin_state());
  EXPECT_DEBUG_CRASH(monitor->set_second_state());
  EXPECT_DEBUG_CRASH(monitor->set_end_state());

  monitor->set_first_state();

  EXPECT_FALSE(monitor->is_begin_state());
  EXPECT_TRUE(monitor->is_first_state());
  EXPECT_FALSE(monitor->is_second_state());
  EXPECT_FALSE(monitor->is_third_state());
  EXPECT_FALSE(monitor->is_end_state());

  EXPECT_DEBUG_CRASH(monitor->set_begin_state());
  EXPECT_DEBUG_CRASH(monitor->set_end_state());
  EXPECT_DEBUG_CRASH(monitor->set_first_state());

  monitor->set_third_state();

  EXPECT_FALSE(monitor->is_begin_state());
  EXPECT_FALSE(monitor->is_first_state());
  EXPECT_FALSE(monitor->is_second_state());
  EXPECT_TRUE(monitor->is_third_state());
  EXPECT_FALSE(monitor->is_end_state());

  EXPECT_DEBUG_CRASH(monitor->set_begin_state());
  EXPECT_DEBUG_CRASH(monitor->set_third_state());
  EXPECT_DEBUG_CRASH(monitor->set_first_state());

  monitor->set_end_state();

  EXPECT_FALSE(monitor->is_begin_state());
  EXPECT_FALSE(monitor->is_first_state());
  EXPECT_FALSE(monitor->is_second_state());
  EXPECT_FALSE(monitor->is_third_state());
  EXPECT_TRUE(monitor->is_end_state());

  EXPECT_DEBUG_CRASH(monitor->set_begin_state());
  EXPECT_DEBUG_CRASH(monitor->set_first_state());
  EXPECT_DEBUG_CRASH(monitor->set_second_state());
  EXPECT_DEBUG_CRASH(monitor->set_third_state());
  EXPECT_DEBUG_CRASH(monitor->set_end_state());
}
