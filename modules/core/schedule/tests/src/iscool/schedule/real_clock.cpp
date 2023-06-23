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
#include "iscool/schedule/real_clock.h"
#include "iscool/schedule/manual_scheduler.h"
#include "iscool/schedule/setup.h"

#include <thread>

#include <gtest/gtest.h>

TEST(iscool_schedule_real_clock, tick)
{
  iscool::schedule::manual_scheduler scheduler;
  iscool::schedule::initialize(scheduler.get_delayed_call_delegate());

  iscool::schedule::real_clock<std::chrono::milliseconds> clock(
      std::chrono::milliseconds(50));

  int calls(0);
  clock.connect_to_tick(
      [&calls]() -> void
      {
        ++calls;
      });

  std::this_thread::sleep_for(std::chrono::milliseconds(49));
  scheduler.update_interval(std::chrono::milliseconds(49));
  EXPECT_EQ(0, calls);

  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  scheduler.update_interval(std::chrono::milliseconds(1));
  EXPECT_EQ(1, calls);

  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  scheduler.update_interval(std::chrono::milliseconds(50));
  EXPECT_EQ(2, calls);

  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  scheduler.update_interval(std::chrono::milliseconds(50));
  EXPECT_EQ(3, calls);

  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  scheduler.update_interval(std::chrono::milliseconds(50));
  EXPECT_EQ(4, calls);

  iscool::schedule::finalize();
}
