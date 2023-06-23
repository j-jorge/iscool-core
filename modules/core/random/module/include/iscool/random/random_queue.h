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
#ifndef ISCOOL_RANDOM_RANDOMQUEUE_H
#define ISCOOL_RANDOM_RANDOMQUEUE_H

#include <deque>
#include <vector>

namespace iscool
{
  namespace random
  {
    template <typename T>
    class random_queue
    {
    public:
      typedef T value_type;

    public:
      void insert(const value_type& value);
      value_type next();

    private:
      void shuffle_next();

    private:
      std::deque<value_type> _next;
      std::vector<value_type> _domain;
    };
  }
}

#include "iscool/random/random_queue.tpp"

#endif
