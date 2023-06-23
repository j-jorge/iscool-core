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
#include "iscool/i18n/relative_past_duration.h"

#include "iscool/time/days.h"

#include "gtest/gtest.h"

TEST(iscool_i18n, relative_past_duration)
{
  EXPECT_EQ("now", iscool::i18n::relative_past_duration(
                       std::chrono::seconds::zero()));
  EXPECT_EQ("now",
            iscool::i18n::relative_past_duration(std::chrono::hours::zero()));
  EXPECT_EQ("now",
            iscool::i18n::relative_past_duration(iscool::time::days::zero()));

  EXPECT_EQ("834 ms. ago", iscool::i18n::relative_past_duration(
                               std::chrono::milliseconds(834)));

  EXPECT_EQ("1 s. ago", iscool::i18n::relative_past_duration(
                            std::chrono::milliseconds(1200)));
  EXPECT_EQ("2 s. ago", iscool::i18n::relative_past_duration(
                            std::chrono::milliseconds(1834)));

  EXPECT_EQ("1 min. ago",
            iscool::i18n::relative_past_duration(std::chrono::seconds(88)));
  EXPECT_EQ("2 min. ago",
            iscool::i18n::relative_past_duration(std::chrono::seconds(118)));

  EXPECT_EQ("1 h. ago",
            iscool::i18n::relative_past_duration(std::chrono::minutes(62)));
  EXPECT_EQ("2 h. ago",
            iscool::i18n::relative_past_duration(std::chrono::minutes(118)));

  EXPECT_EQ("1 day ago",
            iscool::i18n::relative_past_duration(std::chrono::hours(24)));
  EXPECT_EQ("3 days ago",
            iscool::i18n::relative_past_duration(std::chrono::hours(70)));
}
