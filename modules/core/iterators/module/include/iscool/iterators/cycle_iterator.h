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
#ifndef ISCOOL_ITERATORS_CYCLE_ITERATOR_H
#define ISCOOL_ITERATORS_CYCLE_ITERATOR_H

#include <iterator>

namespace iscool
{
    namespace iterators
    {
        template< typename Iterator >
        class cycle_iterator
        {
        public:
            typedef std::forward_iterator_tag iterator_category;

            typedef
            typename std::iterator_traits< Iterator >::value_type value_type;
            
            typedef typename std::iterator_traits< Iterator >::pointer pointer;
            
            typedef
            typename std::iterator_traits< Iterator >::reference reference;
            
        public:
            cycle_iterator( const Iterator& begin, const Iterator& end );

            cycle_iterator< Iterator >& operator++();
            cycle_iterator< Iterator > operator++( int );

            reference operator*() const;
            pointer operator->() const;

        private:
            Iterator _begin;
            Iterator _end;
            Iterator _current;
        };
    }
}

#endif
