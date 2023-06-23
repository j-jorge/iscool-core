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
#include "iscool/profile/scoped_profiler.h"
#include "iscool/profile/setup.h"

#include "iscool/time/now.h"

#include <thread>

#include "iscool/test/equal_collections.h"
#include "iscool/test/no_crash.h"

TEST(iscool_profile, scoped_profiler_not_initialized)
{
  ASSERT_NO_CRASH(iscool::profile::scoped_profiler("scoped"));
}

TEST(iscool_profile, scoped_profiler_output_function_called)
{
  bool called(false);
  iscool::profile::initialize(
      [&called](iscool::profile::profile_data data) -> void
      {
        called = true;
      });

  {
    iscool::profile::scoped_profiler profiler("scoped");
    EXPECT_FALSE(called);
  }
  EXPECT_TRUE(called);
  iscool::profile::finalize();
}

TEST(iscool_profile, scoped_profiler_name)
{
  std::string output;
  iscool::profile::initialize(
      [&output](iscool::profile::profile_data data) -> void
      {
        output = data.name;
      });

  {
    iscool::profile::scoped_profiler profiler("scoped");
  }
  EXPECT_EQ("scoped", output);
  output = std::string();

  {
    iscool::profile::scoped_profiler profiler("scoped");
    profiler.append_tag("tag");
  }
  EXPECT_EQ("scoped", output);
  output = std::string();

  iscool::profile::finalize();
}

TEST(iscool_profile, scoped_profiler_tags)
{
  typedef std::vector<std::string> tag_list;
  tag_list output;
  iscool::profile::initialize(
      [&output](iscool::profile::profile_data data) -> void
      {
        output = data.tags;
      });

  {
    iscool::profile::scoped_profiler profiler("scoped");
    iscool::test::assert_equal_collections(output, tag_list());
  }
  iscool::test::assert_equal_collections(output, tag_list());
  output.clear();

  {
    iscool::profile::scoped_profiler profiler("name");
    profiler.append_tag("1");
    profiler.append_tag("2");
  }
  iscool::test::assert_equal_collections(output, tag_list({ "1", "2" }));
  output.clear();

  iscool::profile::finalize();
}

TEST(iscool_profile, scoped_profiler_duration)
{
  std::chrono::milliseconds output_start(0);
  std::chrono::milliseconds output_end(0);
  iscool::profile::initialize(
      [&output_start, &output_end](iscool::profile::profile_data data) -> void
      {
        output_start = data.start;
        output_end = data.end;
      });

  const std::chrono::milliseconds start(
      iscool::time::now<std::chrono::milliseconds>());
  {
    iscool::profile::scoped_profiler profiler("name");
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
  const std::chrono::milliseconds end(
      iscool::time::now<std::chrono::milliseconds>());

  EXPECT_GE(output_start, start);
  EXPECT_GE(std::chrono::milliseconds(5), output_start - start);

  EXPECT_GE(end, output_end);
  EXPECT_GE(std::chrono::milliseconds(5), end - output_end);

  iscool::profile::finalize();
}
