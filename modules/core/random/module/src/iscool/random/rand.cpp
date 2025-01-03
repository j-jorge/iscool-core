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
#include <iscool/random/rand.hpp>

#include <chrono>

iscool::random::rand& iscool::random::rand::get_default()
{
  static rand defaultInstance;
  return defaultInstance;
}

iscool::random::rand::rand()
  : rand(static_cast<std::size_t>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()))
{}

iscool::random::rand::rand(std::size_t seed)
  : _generator(seed)
{}
