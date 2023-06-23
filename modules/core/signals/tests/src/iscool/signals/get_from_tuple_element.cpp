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
#include "iscool/signals/get_from_tuple_element.h"
#include "iscool/signals/signal.impl.tpp"

#include <string>

#include <gtest/gtest.h>

TEST(iscool_signals_get_from_tuple_element, different_arities)
{
  iscool::signals::signal_collection_from_tuple<
      std::tuple<float, int, std::string>, std::tuple<std::string, float>,
      std::tuple<int>>
      signals;

  iscool::signals::signal<void(int)>& int_0(
      iscool::signals::get_from_tuple_element<int, 0>(signals));

  int_0(23);

  iscool::signals::signal<void(std::string, float)>& float_1(
      iscool::signals::get_from_tuple_element<float, 1>(signals));

  float_1("yep", 4.9);

  iscool::signals::signal<void(float, int, std::string)>& string_2(
      iscool::signals::get_from_tuple_element<std::string, 2>(signals));

  string_2(9.12, 4, "e/a");
}

TEST(iscool_signals_get_from_tuple_element, non_const)
{
  iscool::signals::signal_collection_from_tuple<std::tuple<int, float>,
                                                std::tuple<std::string, float>,
                                                std::tuple<float, int>>
      signals;

  std::string string_string_argument;
  float string_float_argument(0);
  const auto string_callback(
      [&string_string_argument, &string_float_argument](const std::string& s,
                                                        float f) -> void
      {
        string_string_argument = s;
        string_float_argument = f;
      });

  iscool::signals::get_from_tuple_element<std::string, 0>(signals).connect(
      string_callback);

  iscool::signals::signal<void(std::string, float)>& string_0(
      iscool::signals::get_from_tuple_element<std::string, 0>(signals));

  string_0("bac", 49);

  EXPECT_EQ("bac", string_string_argument);
  EXPECT_EQ(49, string_float_argument);

  float int_float_argument(0);
  int int_int_argument(0);
  const auto int_callback(
      [&int_float_argument, &int_int_argument](float f, int i) -> void
      {
        int_float_argument = f;
        int_int_argument = i;
      });

  iscool::signals::get_from_tuple_element<int, 1>(signals).connect(
      int_callback);

  iscool::signals::signal<void(float, int)>& int_1(
      iscool::signals::get_from_tuple_element<int, 1>(signals));

  int_1(2.9, 23);

  EXPECT_FLOAT_EQ(2.9, int_float_argument);
  EXPECT_EQ(23, int_int_argument);
}

TEST(iscool_signals_get_from_tuple_element, const)
{
  typedef iscool::signals::signal_collection_from_tuple<
      std::tuple<int, float>, std::tuple<std::string, float>,
      std::tuple<float, int>>
      signals_type;

  std::string string_string_argument;
  float string_float_argument(0);
  const auto string_callback(
      [&string_string_argument, &string_float_argument](const std::string& s,
                                                        float f) -> void
      {
        string_string_argument = s;
        string_float_argument = f;
      });

  signals_type signals;

  iscool::signals::get_from_tuple_element<std::string, 0>(signals).connect(
      string_callback);

  const signals_type& const_signals(signals);
  const iscool::signals::signal<void(std::string, float)>& string_0(
      iscool::signals::get_from_tuple_element<std::string, 0>(const_signals));

  string_0("abc", 10);

  EXPECT_EQ("abc", string_string_argument);
  EXPECT_EQ(10, string_float_argument);

  float int_float_argument(0);
  int int_int_argument(0);
  const auto int_callback(
      [&int_float_argument, &int_int_argument](float f, int i) -> void
      {
        int_float_argument = f;
        int_int_argument = i;
      });

  iscool::signals::get_from_tuple_element<int, 1>(signals).connect(
      int_callback);

  const iscool::signals::signal<void(float, int)>& int_1(
      iscool::signals::get_from_tuple_element<int, 1>(const_signals));

  int_1(2.9, 23);

  EXPECT_FLOAT_EQ(2.9, int_float_argument);
  EXPECT_EQ(23, int_int_argument);
}
