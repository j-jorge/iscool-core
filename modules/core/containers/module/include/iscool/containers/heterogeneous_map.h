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
#ifndef ISCOOL_CONTAINERS_HETEROGENEOUS_MAP_H
#define ISCOOL_CONTAINERS_HETEROGENEOUS_MAP_H

#include "iscool/optional.h"

#include <unordered_map>
#include <tuple>

namespace iscool
{
    namespace containers
    {
        template< typename Key, typename... T >
        class heterogeneous_map
        {
        public:
            template< typename U >
            void set( const Key& key, const U& value );

            template< typename U >
            bool has( const Key& key ) const;

            template< typename U >
            iscool::optional< U > get( const Key& key ) const;
            
            template< typename U >
            void erase( const Key& key );
            
            template< typename Visitor >
            void visit( Visitor v ) const;

            bool empty() const;

            void swap( heterogeneous_map< Key, T... >& that );

            void clear();
            
        private:
            std::tuple< std::unordered_map< Key, T >... > _maps;
        };
    }
}

#endif
