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
#include <iscool/context.hpp>

#include <iscool/test/debug_crash.hpp>

#include <gtest/gtest.h>

struct iscool_root_context_test : public testing::Test
{
  ic_declare_context(
      _context, ic_context_no_parent_properties,
      ic_context_declare_properties(((int)(root_value))((std::string)(name))));

public:
  context& get_context();
};

iscool_root_context_test::context& iscool_root_context_test::get_context()
{
  return _context;
}

namespace iscool
{
  namespace test
  {
    struct child_context_test
    {
      ic_declare_context(
          _context, ic_context_declare_parent_properties(((int)(root_value))),
          ic_context_declare_properties(
              ((int)(son_value))((std::string)(title))));

    public:
      explicit child_context_test(
          const iscool_root_context_test::context& root_context);

      child_context_test(const iscool_root_context_test::context& root_context,
                         int son, std::string title);

      context& get_context();
    };

    struct child_context_references_parent_test
    {
      ic_declare_context(
          _context,
          ic_context_declare_parent_properties(((const int&)(root_value))),
          ic_context_no_properties);

    public:
      explicit child_context_references_parent_test(
          const iscool_root_context_test::context& root_context);

      context& get_context();
    };

    struct only_parent_properties_test
    {
      ic_declare_context(
          _context, ic_context_declare_parent_properties(((int)(root_value))),
          ic_context_no_properties);
    };
  }
}

iscool::test::child_context_test::child_context_test(
    const iscool_root_context_test::context& root_context)
  : _context(root_context)
{}

iscool::test::child_context_test::child_context_test(
    const iscool_root_context_test::context& root_context, int son,
    std::string title)
  : _context(context(root_context).copy_assign_properties(son, title))
{}

iscool::test::child_context_test::context&
iscool::test::child_context_test::get_context()
{
  return _context;
}

iscool::test::child_context_references_parent_test::
    child_context_references_parent_test(
        const iscool_root_context_test::context& root_context)
  : _context(root_context)
{}


iscool::test::child_context_references_parent_test::context&
iscool::test::child_context_references_parent_test::get_context()
{
  return _context;
}

TEST_F(iscool_root_context_test, values_not_set_at_construction)
{
  EXPECT_FALSE(get_context().is_root_value_set());
  EXPECT_FALSE(get_context().is_name_set());
}

TEST_F(iscool_root_context_test, get_and_set_values)
{
  EXPECT_FALSE(get_context().is_root_value_set());

  get_context().set_root_value(12);

  EXPECT_TRUE(get_context().is_root_value_set());
  EXPECT_EQ(12, get_context().get_root_value());

  EXPECT_FALSE(get_context().is_name_set());

  get_context().set_name("Name");

  EXPECT_TRUE(get_context().is_name_set());
  EXPECT_EQ("Name", get_context().get_name());
}

TEST_F(iscool_root_context_test, values_reset)
{
  get_context().set_root_value(10);
  EXPECT_TRUE(get_context().is_root_value_set());

  get_context().reset_root_value();
  EXPECT_FALSE(get_context().is_root_value_set());

  get_context().set_name("Name");
  EXPECT_TRUE(get_context().is_name_set());

  get_context().reset_name();
  EXPECT_FALSE(get_context().is_name_set());
}

TEST_F(iscool_root_context_test, assert_on_invalid_get)
{
  EXPECT_DEBUG_CRASH(get_context().get_root_value());
  EXPECT_DEBUG_CRASH(get_context().get_name());
}

TEST_F(iscool_root_context_test,
       assert_if_parent_values_not_set_at_construction)
{
  EXPECT_DEBUG_CRASH(iscool::test::child_context_test child(get_context()));
}

TEST_F(iscool_root_context_test, get_value_from_parent)
{
  get_context().set_root_value(10);

  iscool::test::child_context_test child(get_context());

  EXPECT_EQ(10, child.get_context().get_root_value());
}

TEST_F(iscool_root_context_test, values_are_copied)
{
  get_context().set_root_value(10);

  iscool::test::child_context_test child(get_context());

  EXPECT_EQ(10, child.get_context().get_root_value());

  get_context().set_root_value(12);

  EXPECT_EQ(12, get_context().get_root_value());

  EXPECT_EQ(10, child.get_context().get_root_value());
}

TEST_F(iscool_root_context_test, reference_to_parent)
{
  get_context().set_root_value(10);

  iscool::test::child_context_references_parent_test child(get_context());

  EXPECT_EQ(10, child.get_context().get_root_value());

  get_context().set_root_value(12);

  EXPECT_EQ(12, get_context().get_root_value());

  EXPECT_EQ(12, child.get_context().get_root_value());
}

TEST_F(iscool_root_context_test, copy_assign_properties)
{
  get_context().set_root_value(10);
  iscool::test::child_context_test child(get_context(), 12, "test");
  EXPECT_EQ(12, child.get_context().get_son_value());
  EXPECT_EQ("test", child.get_context().get_title());
}
