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
#ifndef ISCOOL_NET_BYTE_ARRAY_H
#define ISCOOL_NET_BYTE_ARRAY_H

#include <vector>
#include <cstdint>

namespace iscool
{
    namespace net
    {
        class byte_array
        {
        private:
            typedef std::vector<std::uint8_t> container;

        public:
            typedef container::iterator iterator;
            typedef container::const_iterator const_iterator;

        public:
            byte_array() = default;
    
            template< typename Iterator >
            byte_array( const Iterator& first, const Iterator& last );

            template< typename T >
            void append( T value );
            void append( const byte_array& array );
            template< typename Iterator >
            void append( const Iterator& first, const Iterator& last );

            std::uint8_t& operator[]( std::size_t index );
            const std::uint8_t& operator[]( std::size_t index ) const;

            iterator begin();
            iterator end();
            
            const_iterator begin() const;
            const_iterator end() const;

            void reserve( std::size_t size );
            std::size_t size() const;

            void swap( byte_array& that );
            
        private:
            container _content;
        };
    }
}

#include "iscool/net/detail/byte_array.tpp"

#endif
