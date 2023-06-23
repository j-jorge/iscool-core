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
#include <iscool/preferences/local_preferences.hpp>

#include <iscool/preferences/property_map.impl.hpp>
#include <iscool/schedule/manual_scheduler.hpp>
#include <iscool/schedule/setup.hpp>

#include <gtest/gtest.h>

class iscool_preferences_local_preferences_test : public ::testing::Test
{
public:
  iscool_preferences_local_preferences_test();
  ~iscool_preferences_local_preferences_test();

protected:
  typedef std::function<void(const iscool::preferences::property_map&)>
      save_function;

protected:
  void wait(std::chrono::milliseconds delay);

private:
  iscool::schedule::manual_scheduler _scheduler;
};

iscool_preferences_local_preferences_test ::
    iscool_preferences_local_preferences_test()
{
  iscool::schedule::initialize(_scheduler.get_delayed_call_delegate());
}

iscool_preferences_local_preferences_test ::
    ~iscool_preferences_local_preferences_test()
{
  iscool::schedule::finalize();
}

void iscool_preferences_local_preferences_test::wait(
    std::chrono::milliseconds delay)
{
  if (delay != std::chrono::milliseconds::zero())
    std::this_thread::sleep_for(delay);

  _scheduler.update_interval(delay);
}

TEST_F(iscool_preferences_local_preferences_test, properties)
{
  iscool::preferences::property_map properties;
  properties.set<std::int64_t>("int64", 24);
  properties.set<std::string>("string", "str");

  iscool::preferences::local_preferences preferences(properties);

  EXPECT_EQ(24, preferences.get_value("int64", std::int64_t(0)));
  EXPECT_EQ("str", preferences.get_value("string", std::string()));

  preferences.set_value("int64", std::int64_t(42));
  preferences.set_value("string", std::string("yep"));
  preferences.set_value("bool", true);
  preferences.flush();

  const iscool::preferences::property_map stored_properties(
      preferences.get_properties());

  EXPECT_EQ(42, *stored_properties.get<std::int64_t>("int64"));
  EXPECT_EQ("yep", *stored_properties.get<std::string>("string"));
  EXPECT_EQ(true, *stored_properties.get<bool>("bool"));
}

TEST_F(iscool_preferences_local_preferences_test, saving_callback)
{
  iscool::preferences::property_map properties;
  properties.set<std::int64_t>("int64", 24);
  properties.set<std::string>("string", "str");

  iscool::preferences::local_preferences preferences(properties);

  bool called(false);

  preferences.connect_to_saving(
      [&](const iscool::preferences::property_map& values) -> void
      {
        called = true;
        EXPECT_EQ("yep", *values.get<std::string>("string"));
        EXPECT_FALSE(!!values.get<std::int64_t>("int64"));
      });

  preferences.set_value("int64", std::int64_t(24));
  preferences.set_value("string", std::string("yep"));

  wait(std::chrono::milliseconds(10));
  EXPECT_TRUE(called);
}
