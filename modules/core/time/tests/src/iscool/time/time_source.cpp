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
#include "iscool/time/now.h"
#include "iscool/time/setup.h"

#include <gtest/gtest.h>

TEST( iscool_time, time_source )
{
    std::chrono::nanoseconds current_date(123);

    iscool::time::scoped_time_source_delegate scoped_time_source
        ([&current_date]() -> std::chrono::nanoseconds
            {
                return current_date;
            });

    EXPECT_EQ(current_date, iscool::time::now<std::chrono::nanoseconds>());
    EXPECT_EQ(current_date, iscool::time::now<std::chrono::nanoseconds>());

    current_date = std::chrono::nanoseconds(666);

    EXPECT_EQ(current_date, iscool::time::now<std::chrono::nanoseconds>());
}