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
#ifndef ISCOOL_RANDOM_DETAIL_DISTINCT_RANDOM_IMPL_TPP
#define ISCOOL_RANDOM_DETAIL_DISTINCT_RANDOM_IMPL_TPP

#include <iscool/random/rand.hpp>

template <typename T>
std::vector<T> iscool::random::distinct_random(std::size_t count, T min, T max)
{
  assert(min <= max);
  assert(static_cast<int>(count) <= max - min + 1);

  static rand& rand(iscool::random::rand::get_default());

  std::vector<T> result(count);
  std::size_t available(max - min + 1);
  std::size_t needed(count);
  std::size_t j(0);

  for (T v(min); needed != 0; ++v, --available)
    if (rand.random<std::size_t>(1, available) <= needed)
      {
        result[j] = v;
        --needed;
        ++j;
      }

  return result;
}

#endif
