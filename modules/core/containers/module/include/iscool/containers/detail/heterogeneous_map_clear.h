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
#ifndef ISCOOL_CONTAINERS_DETAIL_HETEROGENEOUS_MAP_CLEAR_H
#define ISCOOL_CONTAINERS_DETAIL_HETEROGENEOUS_MAP_CLEAR_H

namespace iscool
{
    namespace containers
    {
        namespace detail
        {
            template< std::size_t N >
            struct heterogeneous_map_clear;

            template<>
            struct heterogeneous_map_clear< 0 >
            {
                template< typename T >
                static void run( T );
            };

            template< std::size_t N >
            struct heterogeneous_map_clear
            {
                template< typename Key, typename... T >
                static void run
                ( std::tuple< std::map< Key, T >... >& maps );
            };
        }
    }
}

#include "iscool/containers/detail/heterogeneous_map_clear.tpp"

#endif
