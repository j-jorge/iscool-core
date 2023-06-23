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
#include <iscool/contract/verify_not_null.hpp>
#include <iscool/test/debug_crash.hpp>

#include <gtest/gtest.h>

TEST(iscool_contract_verify_not_null, pointer_ok)
{
  int value;

  int* const result(ic_verify_not_null(&value));
  EXPECT_EQ(&value, result);
}

TEST(iscool_contract_verify_not_null, pointer_null)
{
  EXPECT_DEBUG_CRASH(ic_verify_not_null(nullptr));
}

TEST(iscool_contract_verify_not_null, executed_once)
{
  int calls(0);
  const int value(111);

  const auto predicate(
      [&calls, &value]() -> const int*
      {
        ++calls;
        return &value;
      });

  const int* const result(ic_verify_not_null(predicate()));
  EXPECT_EQ(&value, result);
  EXPECT_EQ(1, calls);
}
