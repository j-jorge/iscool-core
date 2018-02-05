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
#ifndef ISCOOL_JSON_DETAIL_CAST_ARRAY_H
#define ISCOOL_JSON_DETAIL_CAST_ARRAY_H

#include "iscool/json/detail/cast_fwd.h"

#include <array>

namespace Json
{
    class Value;
}

namespace iscool
{
    namespace json
    {
        namespace detail
        {
            template< typename T, std::size_t N >
            struct cast< std::array< T, N > >
            {
                static bool is_valid( const Json::Value& value );
                static std::array< T, N > value( const Json::Value& value );

                template< typename EntryCast >
                static std::array< T, N >
                value( const Json::Value& value, EntryCast entry_cast );
            };
        }
    }
}

#include "iscool/json/detail/cast_array.tpp"

#endif
