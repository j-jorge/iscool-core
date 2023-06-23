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
#include <iscool/strings/format.hpp>

#include <thread>

#include <gtest/gtest.h>

TEST(iscool_strings, format)
{
  EXPECT_EQ("some text", iscool::strings::format("some text"));
  EXPECT_EQ("24", iscool::strings::format("%d", 24));
  EXPECT_EQ("42", iscool::strings::format("%f", 42));
  EXPECT_EQ("%", iscool::strings::format("%%"));
  EXPECT_EQ("text", iscool::strings::format("%s", "text"));
  EXPECT_EQ("answer = 42", iscool::strings::format("%s = %d", "answer", 42));
}

TEST(iscool_strings, thread_safety)
{
  std::vector<std::thread> threads;

  const auto thread_body(
      []() -> void
      {
        for (std::size_t i(0); i != 100; ++i)
          {
            iscool::strings::format("%s = %d", "answer", 42);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
          }
      });

  for (std::size_t i(0); i != 10; ++i)
    threads.emplace_back(thread_body);

  for (std::size_t i(0); i != 10; ++i)
    threads[i].join();
}
