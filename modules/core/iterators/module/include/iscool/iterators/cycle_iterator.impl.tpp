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
#ifndef ISCOOL_ITERATORS_CYCLE_ITERATOR_IMPL_TPP
#define ISCOOL_ITERATORS_CYCLE_ITERATOR_IMPL_TPP

#include <cassert>

template <typename Iterator>
iscool::iterators::cycle_iterator<Iterator>::cycle_iterator(
    const Iterator& begin, const Iterator& end)
  : _begin(begin)
  , _end(end)
  , _current(_begin)
{
  assert(begin != end);
}

template <typename Iterator>
iscool::iterators::cycle_iterator<Iterator>&
iscool::iterators::cycle_iterator<Iterator>::operator++()
{
  ++_current;

  if (_current == _end)
    _current = _begin;

  return *this;
}

template <typename Iterator>
iscool::iterators::cycle_iterator<Iterator>
iscool::iterators::cycle_iterator<Iterator>::operator++(int)
{
  const auto result(*this);
  ++*this;
  return result;
}

template <typename Iterator>
typename iscool::iterators::cycle_iterator<Iterator>::reference
iscool::iterators::cycle_iterator<Iterator>::operator*() const
{
  return *_current;
}

template <typename Iterator>
typename iscool::iterators::cycle_iterator<Iterator>::pointer
iscool::iterators::cycle_iterator<Iterator>::operator->() const
{
  return &*_current;
}

#endif
