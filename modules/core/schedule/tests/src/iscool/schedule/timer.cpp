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
#include <iscool/schedule/timer.hpp>

#include <thread>

#include <gtest/gtest.h>

TEST(iscool_schedule_timer, get_duration)
{
  iscool::schedule::timer timer;
  static constexpr useconds_t milliseconds(1000);

  timer.resume();
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  timer.pause();

  const std::chrono::milliseconds date(
      timer.get_duration<std::chrono::milliseconds>());
  EXPECT_GE(date, std::chrono::milliseconds(190));
  EXPECT_LE(date, std::chrono::milliseconds(210));

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  const std::chrono::milliseconds date_in_pause(
      timer.get_duration<std::chrono::milliseconds>());
  EXPECT_EQ(date, date_in_pause);

  timer.resume();
  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  timer.pause();

  const std::chrono::milliseconds date_resumed(
      timer.get_duration<std::chrono::milliseconds>());
  EXPECT_GE(date_resumed - date, std::chrono::milliseconds(190));
  EXPECT_LE(date_resumed - date, std::chrono::milliseconds(210));
}
