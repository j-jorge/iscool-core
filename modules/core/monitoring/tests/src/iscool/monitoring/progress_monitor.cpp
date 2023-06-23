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
#include "iscool/monitoring/progress_monitor.h"

#include "iscool/test/debug_crash.h"

#include <gtest/gtest.h>

TEST(iscool_monitoring_progress_monitor, single)
{
  iscool::monitoring::progress_monitor monitor;

  float progress(0);
  monitor.connect_to_updated(
      [&progress](float p) -> void
      {
        progress = p;
      });

  EXPECT_FALSE(monitor.is_started());

  EXPECT_DEBUG_CRASH(monitor.begin_monitoring(0));

  monitor.begin_monitoring(10);
  EXPECT_TRUE(monitor.is_started());
  EXPECT_DEBUG_CRASH(monitor.worked(0));
  EXPECT_DEBUG_CRASH(monitor.begin_monitoring(9));

  monitor.worked(1);
  EXPECT_FLOAT_EQ(0.1, progress);

  monitor.worked(4);
  EXPECT_FLOAT_EQ(0.5, progress);

  EXPECT_TRUE(monitor.is_started());

  EXPECT_DEBUG_CRASH(monitor.worked(10));

  monitor.worked(5);
  EXPECT_FLOAT_EQ(1, progress);
  EXPECT_FALSE(monitor.is_started());
}

TEST(iscool_monitoring_progress_monitor, done)
{
  iscool::monitoring::progress_monitor monitor;

  float progress(0);
  monitor.connect_to_updated(
      [&progress](float p) -> void
      {
        progress = p;
      });

  monitor.begin_monitoring(10);
  EXPECT_TRUE(monitor.is_started());

  monitor.worked(1);
  EXPECT_FLOAT_EQ(0.1, progress);

  monitor.done();
  EXPECT_FLOAT_EQ(1, progress);
  EXPECT_FALSE(monitor.is_started());

  monitor.connect_to_updated(
      [](float p) -> void
      {
        EXPECT_FALSE(true);
      });
  monitor.done();
}

TEST(iscool_monitoring_progress_monitor, sub_monitor)
{
  iscool::monitoring::progress_monitor monitor;

  float progress(0);
  monitor.connect_to_updated(
      [&progress](float p) -> void
      {
        progress = p;
      });

  monitor.begin_monitoring(2);

  EXPECT_DEBUG_CRASH(
      iscool::monitoring::progress_monitor sub_monitor(monitor, 3));

  iscool::monitoring::progress_monitor sub_monitor(monitor, 1);

  monitor.worked(1);
  EXPECT_FLOAT_EQ(0.5, progress);

  sub_monitor.begin_monitoring(5);
  sub_monitor.worked(1);
  EXPECT_FLOAT_EQ(0.6, progress);

  sub_monitor.worked(2);
  EXPECT_FLOAT_EQ(0.8, progress);

  sub_monitor.worked(1);
  EXPECT_FLOAT_EQ(0.9, progress);

  sub_monitor.worked(1);
  EXPECT_FLOAT_EQ(1, progress);

  EXPECT_FALSE(sub_monitor.is_started());
  EXPECT_FALSE(monitor.is_started());
}

TEST(iscool_monitoring_progress_monitor, sub_monitor_done)
{
  iscool::monitoring::progress_monitor monitor;

  float progress(0);
  monitor.connect_to_updated(
      [&progress](float p) -> void
      {
        progress = p;
      });

  monitor.begin_monitoring(2);

  iscool::monitoring::progress_monitor sub_monitor(monitor, 1);
  EXPECT_DEBUG_CRASH(sub_monitor.connect_to_updated(
      [](float) -> void
      {
      }));

  sub_monitor.begin_monitoring(5);
  sub_monitor.worked(1);
  EXPECT_FLOAT_EQ(0.1, progress);

  sub_monitor.done();
  EXPECT_FLOAT_EQ(0.5, progress);

  monitor.worked(1);
  EXPECT_FLOAT_EQ(1, progress);
}

TEST(iscool_monitoring_progress_monitor, sub_monitor_on_started)
{
  iscool::monitoring::progress_monitor monitor;

  float progress(0);
  monitor.connect_to_updated(
      [&progress](float p) -> void
      {
        progress = p;
      });

  monitor.begin_monitoring(2);
  monitor.worked(1);

  iscool::monitoring::progress_monitor sub_monitor(monitor, 1);

  sub_monitor.begin_monitoring(5);
  sub_monitor.worked(1);
  EXPECT_FLOAT_EQ(0.6, progress);
}

TEST(iscool_monitoring_progress_monitor, two_sub_monitors)
{
  iscool::monitoring::progress_monitor monitor;

  float progress(0);
  monitor.connect_to_updated(
      [&progress](float p) -> void
      {
        progress = p;
      });

  monitor.begin_monitoring(10);

  iscool::monitoring::progress_monitor sub_monitor_1(monitor, 6);
  sub_monitor_1.begin_monitoring(3);

  iscool::monitoring::progress_monitor sub_monitor_2(monitor, 4);
  sub_monitor_2.begin_monitoring(8);

  sub_monitor_1.worked(1);
  EXPECT_FLOAT_EQ(0.2, progress);

  sub_monitor_1.worked(2);
  EXPECT_FLOAT_EQ(0.6, progress);

  sub_monitor_2.worked(1);
  EXPECT_FLOAT_EQ(0.65, progress);

  sub_monitor_2.worked(1);
  EXPECT_FLOAT_EQ(0.7, progress);

  sub_monitor_2.worked(6);
  EXPECT_FLOAT_EQ(1, progress);
}

TEST(iscool_monitoring_progress_monitor, three_monitor_levels)
{
  iscool::monitoring::progress_monitor monitor;

  float progress(0);
  monitor.connect_to_updated(
      [&progress](float p) -> void
      {
        progress = p;
      });

  monitor.begin_monitoring(10);

  iscool::monitoring::progress_monitor sub_monitor_1(monitor, 4);
  sub_monitor_1.begin_monitoring(2);

  iscool::monitoring::progress_monitor sub_monitor_2(sub_monitor_1, 1);
  sub_monitor_2.begin_monitoring(5);

  sub_monitor_2.worked(1);
  EXPECT_FLOAT_EQ(0.04, progress);

  sub_monitor_1.worked(1);
  EXPECT_FLOAT_EQ(0.24, progress);

  sub_monitor_2.worked(3);
  EXPECT_FLOAT_EQ(0.36, progress);

  sub_monitor_2.worked(1);
  EXPECT_FLOAT_EQ(0.4, progress);

  monitor.worked(1);
  EXPECT_FLOAT_EQ(0.5, progress);
}
