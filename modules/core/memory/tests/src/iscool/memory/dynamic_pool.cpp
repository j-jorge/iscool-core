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
#include "iscool/memory/dynamic_pool.h"

#include <algorithm>
#include <array>

#include <gtest/gtest.h>

namespace iscool
{
    namespace memory
    {
        namespace test
        {
            struct empty_type_traits
            {
                static bool clear( int& i )
                {
                    i = 0xdeadc0de;
                    return true;
                }
            };

            typedef
            iscool::memory::dynamic_pool
            <
                int,
                iscool::memory::test::empty_type_traits
            >
            int_pool;
        }
    }
}

TEST( iscool_memory_dynamic_pool, zero_size )
{
    iscool::memory::test::int_pool pool( 0 );

    auto slot( pool.pick_available() );
    slot.value = 24;

    EXPECT_EQ( 24, pool.get( slot.id ) );
}

TEST( iscool_memory_dynamic_pool, pick_available )
{
    iscool::memory::test::int_pool pool( 10 );

    auto slot1( pool.pick_available() );
    auto slot2( pool.pick_available() );
    auto slot3( pool.pick_available() );

    EXPECT_NE( slot1.id, slot2.id );
    EXPECT_NE( slot1.id, slot3.id );
    EXPECT_NE( slot2.id, slot3.id );
    
    EXPECT_NE( &slot1.value, &slot2.value );
    EXPECT_NE( &slot1.value, &slot3.value );
    EXPECT_NE( &slot2.value, &slot3.value );
}

TEST( iscool_memory_dynamic_pool, grows )
{
    iscool::memory::test::int_pool pool( 1 );

    auto slot1( pool.pick_available() );
    slot1.value = 1;
    
    auto slot2( pool.pick_available() );
    slot2.value = 2;
    
    auto slot3( pool.pick_available() );
    slot3.value = 3;

    EXPECT_EQ( 1, pool.get( slot1.id ) );
    EXPECT_EQ( 2, pool.get( slot2.id ) );
    EXPECT_EQ( 3, pool.get( slot3.id ) );
}

TEST( iscool_memory_dynamic_pool, release_and_reuse )
{
    iscool::memory::test::int_pool pool( 1 );

    auto slot_1( pool.pick_available() );
    const std::size_t id( slot_1.id );
    slot_1.value = 24;
    pool.release( id );
    
    auto slot_2( pool.pick_available() );
    EXPECT_EQ( id, slot_2.id );
    EXPECT_EQ( int( 0xdeadc0de ), slot_2.value );
}

TEST( iscool_memory_dynamic_pool, copy )
{
    iscool::memory::test::int_pool pool_1( 10 );

    auto slot_1( pool_1.pick_available() );
    const std::size_t id( slot_1.id );
    slot_1.value = 742;
    
    iscool::memory::test::int_pool pool_2( pool_1 );

    pool_1.release( id );
    
    EXPECT_EQ( 742, pool_2.get( id ) );
    pool_2.release( id );
}

TEST( iscool_memory_dynamic_pool, clear )
{
   iscool::memory::test::int_pool pool( 10 );

    std::array< std::size_t, 10 > ids;

    for ( std::size_t i( 0 ); i != ids.size(); ++i )
        ids[ i ] = pool.pick_available().id;

    for ( std::size_t i( 1 ); i < ids.size(); i *= 2 )
        pool.release( ids[ i ] );
    
    pool.clear();

    std::array< std::size_t, 10 > cleared_ids;

    for ( std::size_t i( 0 ); i != ids.size(); ++i )
        cleared_ids[ i ] = pool.pick_available().id;

    std::sort( ids.begin(), ids.end() );
    std::sort( cleared_ids.begin(), cleared_ids.end() );
    
    EXPECT_EQ( ids, cleared_ids );
}

namespace iscool
{
    namespace memory
    {
        namespace test
        {
            struct destruction_order
            {
            public:
                void configure
                ( std::size_t i, std::size_t p,
                  std::array< bool, 5 >& dead_flags,
                  std::vector< std::size_t >& destroy_order );

            public:
                std::size_t id;
                std::size_t parent;
                std::array< bool, 5 >* dead;
                std::vector< std::size_t >* order;
            };
            
            struct destruction_order_traits
            {
                static bool clear( destruction_order& self );
            };
        }
    }
}

void iscool::memory::test::destruction_order::configure
( std::size_t i, std::size_t p, std::array< bool, 5 >& dead_flags,
  std::vector< std::size_t >& destroy_order )
{
    id = i;
    parent = p;
    dead = &dead_flags;
    order = &destroy_order;
}

bool iscool::memory::test::destruction_order_traits::clear
( destruction_order& self )
{
    if ( ( self.parent < self.dead->size() )
         && !( *self.dead )[ self.parent ] )
        return false;

    EXPECT_FALSE( ( *self.dead )[ self.id ] );

    ( *self.dead )[ self.id ] = true;
    self.order->push_back( self.id );

    return true;
}

TEST( iscool_memory_dynamic_pool, destruction_order )
{
    static constexpr std::size_t pool_size( 5 );
    
    iscool::memory::dynamic_pool
    <
        iscool::memory::test::destruction_order,
        iscool::memory::test::destruction_order_traits
    > pool( pool_size );
    std::array< bool, pool_size > dead;

    std::vector< std::size_t > destroyed;
    destroyed.reserve( pool_size );
    
    for ( std::size_t i( 0 ); i != pool_size; ++i )
    {
        dead[ i ] = false;
        
        auto slot( pool.pick_available() );
        slot.value.configure
            ( i, std::min( pool_size, 2 * i + 1 ), dead, destroyed );
    }
    
    pool.clear();

    const auto begin( destroyed.begin() );
    const auto end( destroyed.end() );
    
    for ( std::size_t i( 0 ); i != pool_size; ++i )
    {
        const std::size_t parent( 2 * i + 1 );

        if ( parent < pool_size )
            EXPECT_LT
                ( std::find( begin, end, parent ), std::find( begin, end, i ) );
        else
            EXPECT_NE( end, std::find( begin, end, i ) );
    }
}

