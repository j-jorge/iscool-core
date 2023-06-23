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
#include "iscool/monitoring/instant_quality.h"

#include <gtest/gtest.h>

TEST(iscool_monitoring_instant_quality_test, initial_quality)
{
  const iscool::monitoring::instant_quality instant_quality(10);
  EXPECT_FLOAT_EQ(1, instant_quality.get_last_measure());
}

TEST(iscool_monitoring_instant_quality_test, to_zero_then_to_one)
{
  iscool::monitoring::instant_quality instant_quality(3);

  EXPECT_FLOAT_EQ(1, instant_quality.get_last_measure());

  instant_quality.add_attempt();
  instant_quality.add_failure();
  EXPECT_FLOAT_EQ(2.f / 3, instant_quality.get_last_measure());

  instant_quality.add_attempt();
  instant_quality.add_failure();
  EXPECT_FLOAT_EQ(1.f / 3, instant_quality.get_last_measure());

  instant_quality.add_attempt();
  instant_quality.add_failure();
  EXPECT_FLOAT_EQ(0, instant_quality.get_last_measure());

  instant_quality.add_attempt();
  instant_quality.add_success();
  EXPECT_FLOAT_EQ(1.f / 3, instant_quality.get_last_measure());

  instant_quality.add_attempt();
  instant_quality.add_success();
  EXPECT_FLOAT_EQ(2.f / 3, instant_quality.get_last_measure());

  instant_quality.add_attempt();
  instant_quality.add_success();
  EXPECT_FLOAT_EQ(1, instant_quality.get_last_measure());
}

TEST(iscool_monitoring_instant_quality_test, dispatch_changes)
{
  iscool::monitoring::instant_quality instant_quality(3);

  std::size_t calls(0);
  float quality;

  auto change(
      [&calls, &quality](float q) -> void
      {
        ++calls;
        quality = q;
      });

  instant_quality.connect_to_quality_changed(change);

  instant_quality.add_attempt();
  instant_quality.add_success();
  EXPECT_EQ(std::size_t(0), calls);

  instant_quality.add_attempt();
  instant_quality.add_failure();
  EXPECT_EQ(std::size_t(1), calls);
  EXPECT_FLOAT_EQ(2.f / 3, quality);

  instant_quality.add_attempt();
  instant_quality.add_success();
  EXPECT_EQ(std::size_t(1), calls);

  instant_quality.add_attempt();
  instant_quality.add_failure();
  EXPECT_EQ(std::size_t(2), calls);
  EXPECT_FLOAT_EQ(1.f / 3, quality);
}

TEST(iscool_monitoring_instant_quality_test, reset)
{
  iscool::monitoring::instant_quality instant_quality(3);

  instant_quality.add_attempt();
  instant_quality.add_failure();
  EXPECT_FLOAT_EQ(2.f / 3, instant_quality.get_last_measure());

  instant_quality.add_attempt();
  instant_quality.reset();
  EXPECT_FLOAT_EQ(1, instant_quality.get_last_measure());

  instant_quality.add_failure();
  EXPECT_FLOAT_EQ(1, instant_quality.get_last_measure());

  instant_quality.add_attempt();
  instant_quality.add_failure();

  EXPECT_FLOAT_EQ(2.f / 3, instant_quality.get_last_measure());
}
