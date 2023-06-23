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
#include "iscool/random/rand.h"

#include <algorithm>

template <typename T>
void iscool::random::random_queue<T>::insert(const value_type& value)
{
  const typename std::vector<value_type>::const_iterator eit(_domain.end());

  if (std::find(_domain.cbegin(), eit, value) == eit)
    {
      _domain.push_back(value);
      _next.push_back(value);
      shuffle_next();
    }
}

template <typename T>
typename iscool::random::random_queue<T>::value_type
iscool::random::random_queue<T>::next()
{
  if (_domain.empty())
    throw std::out_of_range("There is no value among which to select.");

  if (_next.empty())
    {
      _next.insert(_next.end(), _domain.begin(), _domain.end());
      shuffle_next();
    }

  const value_type result(_next.front());
  _next.pop_front();
  return result;
}

template <typename T>
void iscool::random::random_queue<T>::shuffle_next()
{
  rand::get_default().random_shuffle(_next.begin(), _next.end());
}
