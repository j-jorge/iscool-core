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
#include <iscool/random/random_generator.hpp>

#include <gtest/gtest.h>

#include <map>

TEST(iscool_random_generator, empty_throws)
{
  iscool::random::random_generator<int> generator;

  EXPECT_THROW(generator.get_random(), std::out_of_range);
}

TEST(iscool_random_generator, zero_weightI_is_empty)
{
  iscool::random::random_generator<int> generator;

  generator.set_value_weight(1, 0);
  EXPECT_THROW(generator.get_random(), std::out_of_range);

  generator.set_value_weight(1, 1);
  EXPECT_NO_THROW(generator.get_random());

  generator.set_value_weight(1, 0);
  EXPECT_THROW(generator.get_random(), std::out_of_range);
}

TEST(iscool_random_generator, single_value_always_returned)
{
  iscool::random::random_generator<int> generator;

  generator.set_value_weight(1, 10);

  for (std::size_t i(0); i != 100000; ++i)
    EXPECT_EQ(1, generator.get_random());
}

void assert_equiprobability_on_value_range(std::size_t range_size)
{
  iscool::random::random_generator<int> generator;
  std::map<std::size_t, int> value_count;

  for (std::size_t i(0); i != range_size; ++i)
    {
      generator.set_value_weight(i, 1);
      value_count[i] = 0;
    }

  const std::size_t run_count(100000);

  for (std::size_t i(0); i != run_count; ++i)
    ++value_count[generator.get_random()];

  const int reference_frequency(run_count / range_size);
  const double scale(0.001);
  const int error_threshold_lower_bound(reference_frequency * scale - 1);
  const int error_threshold_upper_bound(error_threshold_lower_bound + 2);

  for (std::size_t i(0); i != range_size; ++i)
    {
      const int frequency(scale * value_count[i]);

      EXPECT_GE(frequency, error_threshold_lower_bound);
      EXPECT_LE(frequency, error_threshold_upper_bound);
    }
}

TEST(iscool_random_generator, equiprobabilityTwoValues)
{
  assert_equiprobability_on_value_range(2);
}

TEST(iscool_random_generator, equiprobabilityFiveValues)
{
  assert_equiprobability_on_value_range(5);
}

TEST(iscool_random_generator, equiprobabilityTenValues)
{
  assert_equiprobability_on_value_range(10);
}

TEST(iscool_random_generator, equiprobabilityFiftyValues)
{
  assert_equiprobability_on_value_range(50);
}

TEST(iscool_random_generator, equiprobabilityOneHundrdeValues)
{
  assert_equiprobability_on_value_range(100);
}

void assert_weighted_probability_on_samples(std::size_t range_size)
{
  iscool::random::random_generator<int> generator;
  std::map<std::size_t, int> value_count;

  for (std::size_t i(1); i <= range_size; ++i)
    {
      generator.set_value_weight(i, i);
      value_count[i] = 0;
    }

  const std::size_t run_count(100000);

  for (std::size_t i(0); i != run_count; ++i)
    ++value_count[generator.get_random()];

  const int population_size(range_size * (range_size + 1) / 2);
  const double scale(0.001);

  for (std::size_t i(1); i <= range_size; ++i)
    {
      const int reference_frequency(i * run_count / population_size);
      const int error_threshold_lower_bound(reference_frequency * scale - 1);
      const int error_threshold_upper_bound(error_threshold_lower_bound + 2);
      const int frequency(scale * value_count[i]);

      EXPECT_GE(frequency, error_threshold_lower_bound);
      EXPECT_LE(frequency, error_threshold_upper_bound);
    }
}

TEST(iscool_random_generator, weightedProbability)
{
  assert_weighted_probability_on_samples(2);
  assert_weighted_probability_on_samples(3);
  assert_weighted_probability_on_samples(5);
  assert_weighted_probability_on_samples(10);
  assert_weighted_probability_on_samples(50);
  assert_weighted_probability_on_samples(100);
}
