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
#ifndef ISCOOL_MEMORY_DETAIL_PIMPL_STORAGE_H
#define ISCOOL_MEMORY_DETAIL_PIMPL_STORAGE_H

#include <memory>
#include <type_traits>

namespace iscool
{
    namespace memory
    {
        namespace detail
        {
            template< typename T, std::size_t N >
            class pimpl_storage
            {
            public:
                template< typename... Args >
                pimpl_storage( Args&&... args );
  
                pimpl_storage( pimpl_storage< T, N >&& ) = delete;
                pimpl_storage( const pimpl_storage< T, N >& ) = delete;
  
                ~pimpl_storage();
  
                pimpl_storage<T, N>&
                operator=( pimpl_storage< T, N >&& ) = delete;

                pimpl_storage<T, N>&
                operator=( const pimpl_storage< T, N >& ) = delete;

                T* get() const;
  
            private:
                typename std::aligned_storage< N >::type _storage;
            };

            template< typename T >
            class pimpl_storage< T, 0 >
            {
            public:
                template< typename... Args >
                pimpl_storage( Args&&... args );
  
                pimpl_storage( pimpl_storage< T, 0 >&& ) = delete;
                pimpl_storage( const pimpl_storage< T, 0 >& ) = delete;
  
                ~pimpl_storage();
  
                pimpl_storage<T, 0>&
                operator=( pimpl_storage< T, 0 >&& ) = delete;

                pimpl_storage<T, 0>&
                operator=( const pimpl_storage< T, 0 >& ) = delete;

                T* get() const;
  
            private:
                std::unique_ptr< T > _pointer;
            };
        }
    }
}
    
#endif
