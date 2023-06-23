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
#ifndef ISCOOL_ITERATORS_BACK_EMPLACE_ITERATOR_H
#define ISCOOL_ITERATORS_BACK_EMPLACE_ITERATOR_H

#include <iterator>

namespace iscool
{
  namespace iterators
  {
    template <typename Container>
    class back_emplace_iterator
      : public std::iterator<std::output_iterator_tag, void, void, void, void>
    {
    public:
      explicit back_emplace_iterator(Container& container);

      back_emplace_iterator&
      operator=(const typename Container::value_type& value);
      back_emplace_iterator& operator=(typename Container::value_type&& value);

      back_emplace_iterator& operator++();
      back_emplace_iterator operator++(int);
      back_emplace_iterator& operator*();

    private:
      Container* _container;
    };

    template <typename Container>
    back_emplace_iterator<Container> back_emplacer(Container& container);
  }
}

#include <iscool/iterators/detail/back_emplace_iterator.tpp>

#endif
