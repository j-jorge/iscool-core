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
#include <iscool/memory/make_unique.hpp>

#include "gtest/gtest.h"

TEST(iscool_memory_make_unique, compilation_test)
{
  std::unique_ptr<int> value(iscool::memory::make_unique<int>(24));

  EXPECT_NE(nullptr, value);
  EXPECT_EQ(24, *value);
}

TEST(iscool_memory_make_unique, perfect_forwarding)
{
  class copy_counter
  {
  public:
    explicit copy_counter(std::size_t& counter)
      : _counter(&counter)
    {}

    copy_counter(const copy_counter& that)
      : _counter(that._counter)
    {
      ++*_counter;
    };

    copy_counter& operator=(const copy_counter& that) = delete;

  private:
    std::size_t* _counter;
  };

  class dummy
  {
  public:
    explicit dummy(const copy_counter& counter)
      : _counter(counter)
    {}

  private:
    copy_counter _counter;
  };

  std::size_t count(0);
  copy_counter counter(count);

  std::unique_ptr<dummy> value(
      iscool::memory::make_unique<dummy>(std::ref(counter)));

  EXPECT_EQ(1, count);
}
