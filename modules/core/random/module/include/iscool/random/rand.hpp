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
#pragma once

#include <boost/random/mersenne_twister.hpp>

#include <concepts>

namespace iscool::random
{
  class rand
  {
  public:
    static rand& get_default();

    rand();
    explicit rand(std::size_t seed);

    template <std::integral T = int>
    T random();

    template <std::integral T>
    T random(T min, T max);

    template <typename InputIterator>
    InputIterator random_in_sequence(InputIterator first, InputIterator last);

    template <typename randomIterator>
    void random_shuffle(randomIterator first, randomIterator last);

  private:
    boost::mt19937_64 _generator;
  };
}

#include <iscool/random/rand.tpp>
