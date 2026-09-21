// SPDX-License-Identifier: Apache-2.0
#include <iscool/time/parse_timestamp.hpp>

#include <gtest/gtest.h>

TEST(iscool_time_parse_time, no_frac)
{
  std::chrono::system_clock::time_point t;

  EXPECT_TRUE(iscool::time::parse_timestamp(t, "1971-02-03T04:05:06Z"));

  const std::chrono::system_clock::time_point expected =
      std::chrono::sys_days(std::chrono::year_month_day(
          std::chrono::year(1971), std::chrono::February,
          std::chrono::day{ 3 }))
      + std::chrono::hours(4) + std::chrono::minutes(5)
      + std::chrono::seconds(6);
  EXPECT_EQ(expected, t);
}

TEST(iscool_time_parse_time, frac)
{
  std::chrono::system_clock::time_point t;

  EXPECT_TRUE(iscool::time::parse_timestamp(t, "1971-02-03T04:05:06.123456Z"));

  const std::chrono::system_clock::time_point expected =
      std::chrono::sys_days(std::chrono::year_month_day(
          std::chrono::year(1971), std::chrono::February,
          std::chrono::day{ 3 }))
      + std::chrono::hours(4) + std::chrono::minutes(5)
      + std::chrono::seconds(6) + std::chrono::microseconds(123456);
  EXPECT_EQ(expected, t);
}

TEST(iscool_time_parse_time, nope)
{
  std::chrono::system_clock::time_point t;

  for (int i = 0; i != 27; ++i)
    {
      char s[] = "1971-02-03T04:05:06.123456Z";
      s[i] = 'a' + i;

      EXPECT_FALSE(iscool::time::parse_timestamp(t, s));
    }

  EXPECT_FALSE(
      iscool::time::parse_timestamp(t, "1971-02-03T04:05:06.123456Zgarbage"));
}
