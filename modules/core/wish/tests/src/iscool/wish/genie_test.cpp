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
#include <iscool/wish/genie.hpp>

#include <iscool/test/debug_crash.hpp>

#include <gtest/gtest.h>

class genie_fixture : public ::testing::Test
{
public:
  genie_fixture();
  void grant_test_wish();

  bool wish_granted() const;

private:
  bool _wish_granted;
};

genie_fixture::genie_fixture()
  : _wish_granted(false)
{}

void genie_fixture::grant_test_wish()
{
  _wish_granted = true;
}

bool genie_fixture::wish_granted() const
{
  return _wish_granted;
}

DECLARE_SIMPLE_WISH(genie_test_wish);

TEST_F(genie_fixture, empower_and_grant)
{
  iscool::wish::genie genie;
  genie.empower<genie_test_wish>(
      std::bind(&genie_fixture::grant_test_wish, this));

  EXPECT_FALSE(wish_granted());
  genie.grant<genie_test_wish>(genie_test_wish());
  EXPECT_TRUE(wish_granted());
}

TEST_F(genie_fixture, double_empower)
{
  iscool::wish::genie genie;
  genie.empower<genie_test_wish>(
      std::bind(&genie_fixture::grant_test_wish, this));
  EXPECT_DEBUG_CRASH(genie.empower<genie_test_wish>(
      std::bind(&genie_fixture::grant_test_wish, this)));
}

TEST(genie, grant_empty_wish)
{
  iscool::wish::genie genie;
  EXPECT_DEBUG_CRASH(genie.grant<genie_test_wish>(genie_test_wish()));
}

TEST(genie, is_wish_valid)
{
  iscool::wish::genie genie;
  EXPECT_FALSE(genie.is_wish_valid<genie_test_wish>());
  genie.empower<genie_test_wish>(
      [](genie_test_wish) -> void
      {
      });
  EXPECT_TRUE(genie.is_wish_valid<genie_test_wish>());
  genie.deny<genie_test_wish>();
  EXPECT_FALSE(genie.is_wish_valid<genie_test_wish>());
}
