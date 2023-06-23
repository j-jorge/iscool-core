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
#include "gtest/gtest.h"

#include <iscool/wish/genie.hpp>
#include <iscool/wish/wish.hpp>
#include <iscool/wish/wishing_well.hpp>

DECLARE_SIMPLE_WISH(simple_test_wish);

TEST(wishing_well, assert_on_fake_wish)
{
  iscool::wish::genie genie;
  iscool::wish::wishing_well well(genie);

  EXPECT_DEATH(well.make_a_wish<simple_test_wish>(), "");
}

TEST(wishing_well, grant_wish)
{
  bool granted{ false };
  iscool::wish::genie genie;
  genie.empower<simple_test_wish>(
      [&granted](const simple_test_wish& wish) -> void
      {
        granted = true;
      });

  iscool::wish::wishing_well well(genie);
  well.make_a_wish<simple_test_wish>();

  EXPECT_TRUE(granted);
}

DECLARE_WISH(test_wish, ((bool)(granted)));

TEST(wishing_well, grant_wish_with_parameters)
{
  bool granted{ false };
  iscool::wish::genie genie;
  genie.empower<test_wish>(
      [&granted](const test_wish& wish) -> void
      {
        granted = wish.get_granted();
      });

  iscool::wish::wishing_well well(genie);
  well.make_a_wish<test_wish>(test_wish(true));

  EXPECT_TRUE(granted);
}

TEST(wishing_well, is_wish_grantable)
{
  iscool::wish::genie genie;
  iscool::wish::wishing_well well(genie);
  EXPECT_FALSE(well.is_wish_grantable<test_wish>());

  bool granted{ false };
  genie.empower<test_wish>(
      [&granted](const test_wish& wish) -> void
      {
        granted = wish.get_granted();
      });
  EXPECT_TRUE(well.is_wish_grantable<test_wish>());

  genie.deny<test_wish>();
  EXPECT_FALSE(well.is_wish_grantable<test_wish>());
}
