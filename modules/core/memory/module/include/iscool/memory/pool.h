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
#ifndef ISCOOL_MEMORY_POOL_H
#define ISCOOL_MEMORY_POOL_H

#include <boost/pool/pool_alloc.hpp>
#include <boost/signals2/dummy_mutex.hpp>

namespace iscool
{
    namespace memory
    {
        template
        <
            typename T,
            typename Mutex = boost::signals2::dummy_mutex
        >
        class pool
        {
        public:
            typedef T* pointer;
            
        public:
            pool();
            ~pool();

            pool( const pool< T, Mutex >& ) = delete;
            pool< T >& operator=( const pool< T, Mutex >& ) = delete;
            
            template< typename... Args >
            pointer construct( Args&&... args );
            
            void destroy( pointer p );
            
        private:
            typedef
            boost::fast_pool_allocator
            <
                T,
                boost::default_user_allocator_malloc_free,
                boost::signals2::dummy_mutex
            > allocator_type;
            
        private:
            Mutex _mutex;
            allocator_type _allocator;
            std::size_t _allocated_count;
        };
    }
}

#endif
