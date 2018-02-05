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
#ifndef ISCOOL_MEMORY_POOL_IMPL_TPP
#define ISCOOL_MEMORY_POOL_IMPL_TPP

#include "iscool/memory/pool.h"

#include <boost/thread/mutex.hpp>

template< typename T, typename Mutex >
iscool::memory::pool< T, Mutex >::pool()
    : _allocated_count( 0 )
{
    
}

template< typename T, typename Mutex >
iscool::memory::pool< T, Mutex >::~pool()
{
    assert( _allocated_count == 0 );
}

template< typename T, typename Mutex >
template< typename... Args >
typename iscool::memory::pool< T, Mutex >::pointer
iscool::memory::pool< T, Mutex >::construct( Args&&... args )
{
    const boost::unique_lock< Mutex > lock( _mutex );
    
    ++_allocated_count;
    
    const pointer result( _allocator.allocate( 1 ) );
    new ( result ) T( std::forward< Args >( args )... );

    return result;
}
            
template< typename T, typename Mutex >
void iscool::memory::pool< T, Mutex >::destroy( pointer p )
{
    const boost::unique_lock< Mutex > lock( _mutex );

    assert( _allocated_count != 0 );
    --_allocated_count;
    
    p->~T();
    _allocator.deallocate( p );
}

#endif
