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
#include "iscool/meta/member_comparator.h"

#include "gtest/gtest.h"

TEST(iscool_meta_member_comparator, less)
{
  struct object
  {
    int value;
  };

  const object a{ 24 };
  const object b{ 42 };

  EXPECT_TRUE(member_comparator(object, .value, <)(a, b));
  EXPECT_FALSE(member_comparator(object, .value, <)(b, a));
}

TEST(iscool_meta_member_comparator, greater)
{
  struct object
  {
    int value;
  };

  const object a{ 24 };
  const object b{ 42 };

  EXPECT_FALSE(member_comparator(object, .value, >)(a, b));
  EXPECT_TRUE(member_comparator(object, .value, >)(b, a));
}

TEST(iscool_meta_member_comparator, equal)
{
  struct object
  {
    int value;
  };

  const object a{ 24 };
  const object b{ 42 };

  EXPECT_FALSE(member_comparator(object, .value, ==)(a, b));
  EXPECT_TRUE(member_comparator(object, .value, ==)(a, a));
}

TEST(iscool_meta_member_comparator, member_function)
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
  const object b{ 42 };

  EXPECT_TRUE(member_comparator(object, .f(), <)(a, b));
  EXPECT_FALSE(member_comparator(object, .f(), <)(b, a));
}

TEST(iscool_meta_member_comparator, pointer_member)
{
  struct object
  {
    int value;
  };

  const object a{ 24 };
  const object b{ 42 };

  EXPECT_TRUE(member_comparator(const object*, ->value, <)(&a, &b));
  EXPECT_FALSE(member_comparator(const object*, ->value, <)(&b, &a));
}
