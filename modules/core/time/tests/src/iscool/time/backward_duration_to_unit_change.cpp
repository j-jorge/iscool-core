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
#include <iscool/time/backward_duration_to_unit_change.hpp>
#include <iscool/time/days.hpp>

#include "gtest/gtest.h"

TEST(iscool_time_backward_duration_to_unit_change, values)
{
  static const std::chrono::seconds second(1);
  static const std::chrono::minutes minute(1);
  static const std::chrono::hours hour(1);
  static const iscool::time::days day(1);

  EXPECT_EQ(
      second,
      iscool::time::backward_duration_to_unit_change<std::chrono::seconds>(
          std::chrono::milliseconds(1)));
  EXPECT_EQ(
      second,
      iscool::time::backward_duration_to_unit_change<std::chrono::seconds>(
          std::chrono::seconds(1)));
  EXPECT_EQ(
      second,
      iscool::time::backward_duration_to_unit_change<std::chrono::seconds>(
          std::chrono::seconds(21)));

  EXPECT_EQ(
      std::chrono::seconds(8),
      iscool::time::backward_duration_to_unit_change<std::chrono::seconds>(
          std::chrono::seconds(67)));
  EXPECT_EQ(
      second,
      iscool::time::backward_duration_to_unit_change<std::chrono::seconds>(
          std::chrono::minutes(1)));
  EXPECT_EQ(
      minute,
      iscool::time::backward_duration_to_unit_change<std::chrono::minutes>(
          std::chrono::seconds(60 + 59)));
  EXPECT_EQ(
      minute,
      iscool::time::backward_duration_to_unit_change<std::chrono::minutes>(
          std::chrono::minutes(2)));

  EXPECT_EQ(
      std::chrono::minutes(4),
      iscool::time::backward_duration_to_unit_change<std::chrono::minutes>(
          std::chrono::minutes(63)));
  EXPECT_EQ(
      minute,
      iscool::time::backward_duration_to_unit_change<std::chrono::minutes>(
          std::chrono::hours(1)));
  EXPECT_EQ(hour,
            iscool::time::backward_duration_to_unit_change<std::chrono::hours>(
                std::chrono::minutes(60 + 59)));
  EXPECT_EQ(hour,
            iscool::time::backward_duration_to_unit_change<std::chrono::hours>(
                std::chrono::hours(2)));

  EXPECT_EQ(hour,
            iscool::time::backward_duration_to_unit_change<std::chrono::hours>(
                std::chrono::hours(26)));
  EXPECT_EQ(hour,
            iscool::time::backward_duration_to_unit_change<std::chrono::hours>(
                iscool::time::days(1)));
  EXPECT_EQ(day,
            iscool::time::backward_duration_to_unit_change<iscool::time::days>(
                std::chrono::hours(24 + 23)));
  EXPECT_EQ(day,
            iscool::time::backward_duration_to_unit_change<iscool::time::days>(
                iscool::time::days(2)));
}
