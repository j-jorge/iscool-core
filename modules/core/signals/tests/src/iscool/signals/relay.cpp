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
#include <iscool/signals/relay.hpp>
#include <iscool/signals/signal.impl.tpp>

#include "gtest/gtest.h"

TEST(iscool_signals_relay, empty_relay)
{
  iscool::signals::signal<void()> first_signal;
  bool called(false);
  first_signal.connect(
      [&called]() -> void
      {
        called = true;
      });

  iscool::signals::signal<void()> second_signal;

  second_signal.connect(iscool::signals::relay(first_signal));
  second_signal();

  EXPECT_TRUE(called);
}

class generic_slot
{
public:
  template <typename R, typename... T>
  R slot(T... args);

  template <typename R>
  R result_slot();

  template <typename... T>
  void void_slot_with_params(T... args);

  void void_slot();

  std::size_t get_call_count() const;

private:
  std::size_t _call_count = 0ull;
};

template <typename R, typename... T>
R generic_slot::slot(T... args)
{
  ++_call_count;
  return R();
}

template <typename R>
R generic_slot::result_slot()
{
  ++_call_count;
  return R();
}

template <typename... T>
void generic_slot::void_slot_with_params(T... args)
{
  ++_call_count;
}

void generic_slot::void_slot()
{
  ++_call_count;
}

std::size_t generic_slot::get_call_count() const
{
  return _call_count;
}

TEST(iscool_signals_relay, simple_signal_relay)
{
  iscool::signals::signal<void()> first_signal;
  iscool::signals::signal<void()> second_signal;

  generic_slot slot;
  first_signal.connect(std::bind(&generic_slot::void_slot, &slot));
  second_signal.connect(iscool::signals::relay(first_signal));

  EXPECT_EQ(0ull, slot.get_call_count());
  slot.void_slot();
  EXPECT_EQ(1ull, slot.get_call_count());
  first_signal();
  EXPECT_EQ(2ull, slot.get_call_count());
  second_signal();
  EXPECT_EQ(3ull, slot.get_call_count());
  second_signal();
  EXPECT_EQ(4ull, slot.get_call_count());
}

TEST(iscool_signals_relay, signal_with_one_argument)
{
  iscool::signals::signal<void(int)> first_signal, second_signal;

  generic_slot slot;
  first_signal.connect(std::bind(&generic_slot::void_slot_with_params<int>,
                                 &slot, std::placeholders::_1));
  second_signal.connect(iscool::signals::relay(first_signal));

  second_signal(0);
  EXPECT_EQ(1ull, slot.get_call_count());

  second_signal(13);
  EXPECT_EQ(2ull, slot.get_call_count());
}

TEST(iscool_signals_relay, signal_with_multiple_arguments)
{
  iscool::signals::signal<void(int, float, char)> first_signal, second_signal;

  generic_slot slot;
  first_signal.connect(std::bind(
      &generic_slot::void_slot_with_params<int, float, char>, &slot,
      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

  second_signal.connect(iscool::signals::relay(first_signal));

  second_signal(0, 0.5f, 'a');
  EXPECT_EQ(1ull, slot.get_call_count());

  second_signal(12, -12.0f, 'c');
  EXPECT_EQ(2ull, slot.get_call_count());
}

TEST(iscool_signals_relay, multiple_relay)
{
  iscool::signals::signal<void()> first_signal, second_signal;

  generic_slot slot;
  first_signal.connect(std::bind(&generic_slot::void_slot, &slot));
  second_signal.connect(iscool::signals::relay(first_signal));
  second_signal.connect(iscool::signals::relay(first_signal));

  second_signal();
  EXPECT_EQ(2ull, slot.get_call_count());
  second_signal();
  EXPECT_EQ(4ull, slot.get_call_count());
}

TEST(iscool_signals_relay, multiple_slot)
{
  iscool::signals::signal<void()> first_signal, second_signal;

  generic_slot slot;
  first_signal.connect(std::bind(&generic_slot::void_slot, &slot));
  first_signal.connect(std::bind(&generic_slot::void_slot, &slot));
  first_signal.connect(std::bind(&generic_slot::void_slot, &slot));
  second_signal.connect(iscool::signals::relay(first_signal));

  second_signal();
  EXPECT_EQ(3ull, slot.get_call_count());
  second_signal();
  EXPECT_EQ(6ull, slot.get_call_count());
}

struct store_parameters
{
  void slot(int a, float b, char c);

  int _a = 0;
  float _b = 0.0f;
  char _c = '0';
};

void store_parameters::slot(int a, float b, char c)
{
  _a = a;
  _b = b;
  _c = c;
}

TEST(iscool_signals_relay, relay_parameters)
{
  iscool::signals::signal<void(int, float, char)> first_signal, second_signal;

  store_parameters store;
  first_signal.connect(std::bind(&store_parameters::slot, &store,
                                 std::placeholders::_1, std::placeholders::_2,
                                 std::placeholders::_3));
  second_signal.connect(iscool::signals::relay(first_signal));

  store.slot(1, 1.0f, '1');
  EXPECT_EQ(1, store._a);
  EXPECT_EQ(1.0f, store._b);
  EXPECT_EQ('1', store._c);

  first_signal(2, 2.0f, '2');
  EXPECT_EQ(2, store._a);
  EXPECT_EQ(2.0f, store._b);
  EXPECT_EQ('2', store._c);

  second_signal(3, 3.0f, '3');
  EXPECT_EQ(3, store._a);
  EXPECT_EQ(3.0f, store._b);
  EXPECT_EQ('3', store._c);
}

TEST(iscool_signals_relay, disconnect_relay)
{
  iscool::signals::signal<void()> first_signal, second_signal;

  generic_slot slot;
  first_signal.connect(std::bind(&generic_slot::void_slot, &slot));
  iscool::signals::connection relay_connection(
      second_signal.connect(iscool::signals::relay(first_signal)));

  EXPECT_EQ(0ull, slot.get_call_count());
  second_signal();
  EXPECT_EQ(1ull, slot.get_call_count());
  relay_connection.disconnect();
  second_signal();
  EXPECT_EQ(1ull, slot.get_call_count());
}

TEST(iscool_signals_relay, relay_parameters_preset)
{
  iscool::signals::signal<void(int, float, char)> first_signal, second_signal;

  store_parameters store;
  first_signal.connect(std::bind(&store_parameters::slot, &store,
                                 std::placeholders::_1, 12.f,
                                 std::placeholders::_3));
  second_signal.connect(iscool::signals::relay(first_signal));

  second_signal(1, 1.0f, '1');
  EXPECT_EQ(1, store._a);
  EXPECT_EQ(12.f, store._b);
  EXPECT_EQ('1', store._c);
}

TEST(iscool_signals_relay, relay_placeholder_swap)
{
  iscool::signals::signal<void(int, float, char)> first_signal, second_signal;

  store_parameters store;
  first_signal.connect(std::bind(&store_parameters::slot, &store,
                                 std::placeholders::_2, std::placeholders::_1,
                                 std::placeholders::_3));
  second_signal.connect(iscool::signals::relay(first_signal));

  second_signal(12, 1.0f, '1');
  EXPECT_EQ(1, store._a);
  EXPECT_EQ(12.f, store._b);
  EXPECT_EQ('1', store._c);
}
