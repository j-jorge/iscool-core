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
#include "iscool/meta/member_constant_equality.h"

#include "gtest/gtest.h"

TEST(iscool_meta_member_constant_equality, direct_member)
{
  struct object
  {
    int value;
  };

  const object a{ 24 };

  EXPECT_TRUE(member_constant_equality(object, .value, 24)(a));
  EXPECT_FALSE(member_constant_equality(object, .value, 4)(a));
}

TEST(iscool_meta_member_constant_equality, no_member)
{
  const int a(24);

  EXPECT_TRUE(member_constant_equality(int, , 24)(a));
  EXPECT_FALSE(member_constant_equality(int, , 4)(a));
}

TEST(iscool_meta_member_constant_equality, member_function)
{
  struct object
  {
    int value;

    int f() const
    {
      return value;
    }
  };

  const object a{ 24 };

  EXPECT_TRUE(member_constant_equality(object, .f(), 24)(a));
  EXPECT_FALSE(member_constant_equality(object, .f(), 42)(a));
}

TEST(iscool_meta_member_constant_equality, pointer_member)
{
  struct object
  {
    int value;
  };

  const object a{ 24 };
  const object b{ 42 };

  EXPECT_TRUE(member_constant_equality(const object*, ->value, 24)(&a));
  EXPECT_FALSE(member_constant_equality(const object*, ->value, b.value)(&a));
}
