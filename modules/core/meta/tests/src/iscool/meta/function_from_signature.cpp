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
#include "iscool/meta/function_from_signature.h"

#include "gtest/gtest.h"

TEST(iscool_underlying_type, default_void_void)
{
  iscool::meta::function_from_signature<void>::type f1(
      []() -> void
      {
      });
  iscool::meta::function_from_signature<void, void>::type f2(
      []() -> void
      {
      });
}

TEST(iscool_underlying_type, default_void_args)
{
  iscool::meta::function_from_signature<void, int>::type f1(
      [](int) -> void
      {
      });
  iscool::meta::function_from_signature<void, int, float>::type f2(
      [](int, float) -> void
      {
      });
}

TEST(iscool_underlying_type, default_int_void)
{
  iscool::meta::function_from_signature<int>::type f1(
      []() -> int
      {
        return 0;
      });
  iscool::meta::function_from_signature<int, void>::type f2(
      []() -> int
      {
        return 0;
      });
}

TEST(iscool_underlying_type, default_int_args)
{
  iscool::meta::function_from_signature<int, int>::type f1(
      [](int) -> int
      {
        return 0;
      });
  iscool::meta::function_from_signature<int, int, float>::type f2(
      [](int, float) -> int
      {
        return 0;
      });
}

TEST(iscool_underlying_type, std_function_void_void)
{
  iscool::meta::function_from_signature<void>::in_functor<std::function>::type
  f1(
      []() -> void
      {
      });
  iscool::meta::function_from_signature<void,
                                        void>::in_functor<std::function>::type
  f2(
      []() -> void
      {
      });
}

TEST(iscool_underlying_type, std_function_void_args)
{
  iscool::meta::function_from_signature<void,
                                        int>::in_functor<std::function>::type
  f1(
      [](int) -> void
      {
      });
  iscool::meta::function_from_signature<void, int,
                                        float>::in_functor<std::function>::type
  f2(
      [](int, float) -> void
      {
      });
}

TEST(iscool_underlying_type, std_function_int_void)
{
  iscool::meta::function_from_signature<int>::in_functor<std::function>::type
  f1(
      []() -> int
      {
        return 0;
      });
  iscool::meta::function_from_signature<int,
                                        void>::in_functor<std::function>::type
  f2(
      []() -> int
      {
        return 0;
      });
}

TEST(iscool_underlying_type, std_function_int_args)
{
  iscool::meta::function_from_signature<int,
                                        int>::in_functor<std::function>::type
  f1(
      [](int) -> int
      {
        return 0;
      });
  iscool::meta::function_from_signature<int, int,
                                        float>::in_functor<std::function>::type
  f2(
      [](int, float) -> int
      {
        return 0;
      });
}

template <typename Signature>
class custom_functor
{
public:
  template <typename F>
  custom_functor(F f){};
};

TEST(iscool_underlying_type, custom_void_void)
{
  iscool::meta::function_from_signature<void>::in_functor<custom_functor>::type
  f1(
      []() -> void
      {
      });
  iscool::meta::function_from_signature<void,
                                        void>::in_functor<custom_functor>::type
  f2(
      []() -> void
      {
      });
}

TEST(iscool_underlying_type, custom_void_args)
{
  iscool::meta::function_from_signature<void,
                                        int>::in_functor<custom_functor>::type
  f1(
      [](int) -> void
      {
      });
  iscool::meta::function_from_signature<void, int, float>::in_functor<
      custom_functor>::type
  f2(
      [](int, float) -> void
      {
      });
}

TEST(iscool_underlying_type, custom_int_void)
{
  iscool::meta::function_from_signature<int>::in_functor<custom_functor>::type
  f1(
      []() -> int
      {
        return 0;
      });
  iscool::meta::function_from_signature<int,
                                        void>::in_functor<custom_functor>::type
  f2(
      []() -> int
      {
        return 0;
      });
}

TEST(iscool_underlying_type, custom_int_args)
{
  iscool::meta::function_from_signature<int,
                                        int>::in_functor<custom_functor>::type
  f1(
      [](int) -> int
      {
        return 0;
      });
  iscool::meta::function_from_signature<int, int, float>::in_functor<
      custom_functor>::type
  f2(
      [](int, float) -> int
      {
        return 0;
      });
}
