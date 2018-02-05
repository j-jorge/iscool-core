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
#ifndef ISCOOL_STRINGS_STR_CONST_H
#define ISCOOL_STRINGS_STR_CONST_H

#include "iscool/strings/hash_type.h"

#include <cstddef>

namespace iscool
{
    namespace strings
    {
        class str_const
        {
        public:
            template< std::size_t N >
            constexpr str_const( const char (&s)[ N ] );

            constexpr operator const char *() const;

            constexpr std::size_t size() const;

            constexpr hash_type hash() const;

        private:
            constexpr hash_type hash( std::size_t pos ) const;

        private:
            const char* const _begin;
            const std::size_t _size;
        };
    }
}

#include "iscool/strings/detail/str_const.tpp"

#endif

