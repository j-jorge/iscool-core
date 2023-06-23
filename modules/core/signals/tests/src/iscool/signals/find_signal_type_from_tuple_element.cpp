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
#include "iscool/signals/find_signal_type_from_tuple_element.h"
#include "iscool/signals/signal.impl.tpp"

#include <string>

#include <gtest/gtest.h>

TEST(iscool_signals_find_signal_type_from_tuple_element, find)
{
  typedef iscool::signals::signal_collection_from_tuple<
      std::tuple<int, float>, std::tuple<std::string, float>,
      std::tuple<float, int>>
      signals;

  const bool string_0(
      std::is_same<iscool::signals::signal<void(std::string, float)>,
                   iscool::signals::find_signal_type_from_tuple_element<
                       std::string, 0, signals>::type>::value);
  EXPECT_TRUE(string_0);

  const bool int_0(
      std::is_same<iscool::signals::signal<void(int, float)>,
                   iscool::signals::find_signal_type_from_tuple_element<
                       int, 0, signals>::type>::value);
  EXPECT_TRUE(int_0);

  const bool int_1(
      std::is_same<iscool::signals::signal<void(float, int)>,
                   iscool::signals::find_signal_type_from_tuple_element<
                       int, 1, signals>::type>::value);
  EXPECT_TRUE(int_1);

  const bool float_0(
      std::is_same<iscool::signals::signal<void(float, int)>,
                   iscool::signals::find_signal_type_from_tuple_element<
                       float, 0, signals>::type>::value);
  EXPECT_TRUE(float_0);

  const bool float_1(
      std::is_same<iscool::signals::signal<void(int, float)>,
                   iscool::signals::find_signal_type_from_tuple_element<
                       float, 1, signals>::type>::value);
  EXPECT_TRUE(float_1);
}
