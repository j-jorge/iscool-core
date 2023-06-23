#include <iscool/schedule/command_queue.hpp>

#include <gtest/gtest.h>

namespace iscool
{
  namespace schedule
  {
    namespace test
    {
      static int command_queue_free_function_calls;
      static void command_queue_free_function()
      {
        ++command_queue_free_function_calls;
      }
    }
  }
}

TEST(iscool_schedule_command_queue, execute)
{
  struct object
  {
    void member(int v)
    {
      value += v;
    }
    int value = 0;
  } object;

  struct functor
  {
    void operator()(int v)
    {
      value += v;
    }
    int& value;
  };

  int functor_calls(0);
  int lambda_calls(0);

  iscool::schedule::command_queue commands;

  iscool::schedule::test::command_queue_free_function_calls = 0;

  commands.queue(&iscool::schedule::test::command_queue_free_function);
  commands.queue(&object::member, &object, 2);
  commands.queue(functor{ functor_calls }, 3);
  commands.queue(
      [&](int v) -> void
      {
        lambda_calls += v;
      },
      4);

  EXPECT_EQ(0, iscool::schedule::test::command_queue_free_function_calls);
  EXPECT_EQ(0, object.value);
  EXPECT_EQ(0, functor_calls);
  EXPECT_EQ(0, lambda_calls);
  EXPECT_FALSE(commands.empty());

  commands.execute_next();

  EXPECT_EQ(1, iscool::schedule::test::command_queue_free_function_calls);
  EXPECT_EQ(0, object.value);
  EXPECT_EQ(0, functor_calls);
  EXPECT_EQ(0, lambda_calls);
  EXPECT_FALSE(commands.empty());

  commands.execute_next();

  EXPECT_EQ(1, iscool::schedule::test::command_queue_free_function_calls);
  EXPECT_EQ(2, object.value);
  EXPECT_EQ(0, functor_calls);
  EXPECT_EQ(0, lambda_calls);
  EXPECT_FALSE(commands.empty());

  commands.execute_next();

  EXPECT_EQ(1, iscool::schedule::test::command_queue_free_function_calls);
  EXPECT_EQ(2, object.value);
  EXPECT_EQ(3, functor_calls);
  EXPECT_EQ(0, lambda_calls);
  EXPECT_FALSE(commands.empty());

  commands.execute_next();

  EXPECT_EQ(1, iscool::schedule::test::command_queue_free_function_calls);
  EXPECT_EQ(2, object.value);
  EXPECT_EQ(3, functor_calls);
  EXPECT_EQ(4, lambda_calls);
  EXPECT_TRUE(commands.empty());
}

TEST(iscool_schedule_command_queue, clear)
{
  iscool::schedule::command_queue commands;

  EXPECT_TRUE(commands.empty());

  commands.queue(
      []() -> void
      {
      });
  commands.queue(
      []() -> void
      {
      });

  commands.execute_next();
  EXPECT_FALSE(commands.empty());

  commands.clear();
  EXPECT_TRUE(commands.empty());

  iscool::schedule::test::command_queue_free_function_calls = 0;

  commands.queue(&iscool::schedule::test::command_queue_free_function);
  EXPECT_FALSE(commands.empty());

  commands.execute_next();

  EXPECT_EQ(1, iscool::schedule::test::command_queue_free_function_calls);
  EXPECT_TRUE(commands.empty());
}
