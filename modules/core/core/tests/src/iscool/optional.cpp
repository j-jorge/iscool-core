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
#include "iscool/optional.h"
#include "iscool/none.h"
#include "iscool/optional.impl.tpp"

#include <string>

#include <gtest/gtest.h>

template <typename T>
class iscool_optional_test : public testing::Test
{};

namespace iscool
{
  namespace test
  {
    template <typename T>
    T value_factory();

    template <>
    int value_factory<int>();

    template <>
    std::string value_factory<std::string>();

    template <typename T>
    struct deep_equality
    {
      static void test(const T& value, const iscool::optional<T>& optional);
    };

    template <typename T>
    struct deep_equality<T&>
    {
      static void test(const T& value, const iscool::optional<T&>& optional);
    };
  }
}

template <>
int iscool::test::value_factory<int>()
{
  return 24;
}

template <>
std::string iscool::test::value_factory<std::string>()
{
  return "abc";
}

template <typename T>
void iscool::test::deep_equality<T>::test(const T& value,
                                          const iscool::optional<T>& optional)
{
  EXPECT_EQ(value, *optional);
}

template <typename T>
void iscool::test::deep_equality<T&>::test(
    const T& value, const iscool::optional<T&>& optional)
{
  EXPECT_EQ(&value, &*optional);
}

typedef testing::Types<int, int&, const int&,

                       std::string, std::string&, const std::string&>
    value_types;

TYPED_TEST_CASE(iscool_optional_test, value_types);

TYPED_TEST(iscool_optional_test, empty)
{
  iscool::optional<TypeParam> optional;
  EXPECT_FALSE(!!optional);

  EXPECT_EQ(iscool::none, optional);
  EXPECT_EQ(optional, iscool::none);
}

TYPED_TEST(iscool_optional_test, construct_from_value)
{
  typedef iscool::optional<TypeParam> optional_type;
  typedef typename std::decay<TypeParam>::type value_type;

  value_type value(iscool::test::value_factory<value_type>());
  const optional_type optional(value);

  EXPECT_TRUE(!!optional);
  iscool::test::deep_equality<TypeParam>::test(value, optional);
}

TYPED_TEST(iscool_optional_test, construct_from_optional_empty)
{
  typedef iscool::optional<TypeParam> optional_type;

  optional_type optional;
  optional_type copy(optional);

  EXPECT_FALSE(!!optional);
  EXPECT_FALSE(!!copy);
}

TYPED_TEST(iscool_optional_test, construct_from_optional_non_empty)
{
  typedef iscool::optional<TypeParam> optional_type;
  typedef typename std::decay<TypeParam>::type value_type;

  value_type value(iscool::test::value_factory<value_type>());

  const optional_type optional(value);
  const optional_type copy(optional);

  EXPECT_TRUE(!!optional);
  iscool::test::deep_equality<TypeParam>::test(value, optional);
  EXPECT_TRUE(!!copy);
  iscool::test::deep_equality<TypeParam>::test(value, copy);
}

TYPED_TEST(iscool_optional_test, construct_from_moved_optional)
{
  typedef iscool::optional<TypeParam> optional_type;
  typedef typename std::decay<TypeParam>::type value_type;

  value_type value(iscool::test::value_factory<value_type>());

  optional_type optional(value);
  const optional_type copy(std::move(optional));

  EXPECT_TRUE(!!copy);
  iscool::test::deep_equality<TypeParam>::test(value, copy);
}

TYPED_TEST(iscool_optional_test, dereference)
{
  typedef iscool::optional<TypeParam> optional_type;
  typedef typename std::decay<TypeParam>::type value_type;

  value_type value(iscool::test::value_factory<value_type>());

  const optional_type optional(value);

  EXPECT_EQ(optional.operator->(), &*optional);
}

TYPED_TEST(iscool_optional_test, test_assign_value)
{
  typedef iscool::optional<TypeParam> optional_type;
  typedef typename std::decay<TypeParam>::type value_type;

  value_type value(iscool::test::value_factory<value_type>());

  optional_type optional;
  optional = value;

  iscool::test::deep_equality<TypeParam>::test(value, optional);
}

TYPED_TEST(iscool_optional_test, assign_optional)
{
  typedef iscool::optional<TypeParam> optional_type;
  typedef typename std::decay<TypeParam>::type value_type;

  value_type value(iscool::test::value_factory<value_type>());

  optional_type copy;
  const optional_type optional(value);

  copy = optional;

  iscool::test::deep_equality<TypeParam>::test(value, optional);
  iscool::test::deep_equality<TypeParam>::test(value, copy);
}

TYPED_TEST(iscool_optional_test, assign_moved_optional)
{
  typedef iscool::optional<TypeParam> optional_type;
  typedef typename std::decay<TypeParam>::type value_type;

  value_type value(iscool::test::value_factory<value_type>());

  optional_type copy;
  const optional_type optional(value);

  copy = std::move(optional);

  EXPECT_TRUE(!!copy);
  iscool::test::deep_equality<TypeParam>::test(value, copy);
}

TYPED_TEST(iscool_optional_test, emplace)
{
  typedef iscool::optional<TypeParam> optional_type;
  typedef typename std::decay<TypeParam>::type value_type;

  value_type value(iscool::test::value_factory<value_type>());

  optional_type optional;
  optional.emplace(value);

  iscool::test::deep_equality<TypeParam>::test(value, optional);
}

TYPED_TEST(iscool_optional_test, none)
{
  typedef iscool::optional<TypeParam> optional_type;
  typedef typename std::decay<TypeParam>::type value_type;

  value_type value(iscool::test::value_factory<value_type>());

  optional_type optional(value);

  optional = iscool::none;

  EXPECT_EQ(iscool::none, optional);
  EXPECT_EQ(optional, iscool::none);
  EXPECT_FALSE(!!optional);
}

TYPED_TEST(iscool_optional_test, swap)
{
  typedef iscool::optional<TypeParam> optional_type;
  typedef typename std::decay<TypeParam>::type value_type;

  value_type value_1(iscool::test::value_factory<value_type>());
  value_type value_2(value_1 + value_1);

  optional_type optional_1(value_1);
  optional_type optional_2(value_2);

  optional_1.swap(optional_2);

  iscool::test::deep_equality<TypeParam>::test(value_2, optional_1);
  iscool::test::deep_equality<TypeParam>::test(value_1, optional_2);
}

TEST(iscool_optional_test, emplace_arguments)
{
  iscool::optional<std::string> optional;
  optional.emplace(2, 'a');

  EXPECT_TRUE(!!optional);
  EXPECT_EQ(std::size_t(2), optional->size());
  EXPECT_EQ('a', (*optional)[0]);
  EXPECT_EQ('a', (*optional)[1]);
}

TEST(iscool_optional_test, reference)
{
  int value(999);
  iscool::optional<int&> optional(value);
  iscool::optional<int&> copy(optional);

  int value_2(111);
  optional = value_2;

  EXPECT_EQ(&value_2, &*optional);
  EXPECT_EQ(&value, &*copy);
}

TEST(iscool_optional_test, destructor)
{
  struct destructor_observer
  {
  public:
    destructor_observer(std::size_t& calls)
      : _calls(calls)
    {}

    ~destructor_observer()
    {
      ++_calls;
    }

  private:
    std::size_t& _calls;
  };

  std::size_t calls(0);

  {
    iscool::optional<destructor_observer> optional;
    optional.emplace(calls);
  }

  EXPECT_EQ(std::size_t(1), calls);

  calls = 0;
  destructor_observer observer(calls);

  {
    iscool::optional<destructor_observer&> optional(observer);
  }

  EXPECT_EQ(std::size_t(0), calls);
}

TEST(iscool_optional_test, cast)
{
  iscool::optional<int> optional_int(1.0);
  EXPECT_EQ(1, *optional_int);

  iscool::optional<float> optional_float(optional_int);
  EXPECT_FLOAT_EQ(1, *optional_float);

  optional_float = 1.5;
  EXPECT_FLOAT_EQ(1.5, *optional_float);

  iscool::optional<int> optional_int_copy(optional_float);
  EXPECT_EQ(1, *optional_int_copy);
}

TEST(iscool_optional_test, reference_to_derived)
{
  struct base
  {
    int a;
  };

  struct derived : public base
  {
    int b;
  };

  derived d;
  d.a = 392;

  iscool::optional<base&> optional(d);
  EXPECT_EQ(&d, &*optional);
  EXPECT_EQ(392, optional->a);
}

TEST(iscool_optional_test, assign_non_reference_from_reference)
{
  const int value(93);
  const iscool::optional<const int&> reference(value);
  const iscool::optional<int> optional(reference);

  EXPECT_EQ(&value, &*reference);
  EXPECT_EQ(value, *optional);
}

TEST(iscool_optional_test, make_optional)
{
  const int value(93);
  auto optional(iscool::make_optional(value));

  const bool is_expected_type(
      std::is_same<iscool::optional<int>, decltype(optional)>::value);

  EXPECT_TRUE(is_expected_type);
  EXPECT_TRUE(!!optional);
  EXPECT_EQ(value, *optional);
}
