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
#include "iscool/memory/pimpl.impl.tpp"

#include "gtest/gtest.h"

TEST( iscool_memory_pimpl, unknown_size_auto_allocation )
{
    iscool::memory::pimpl< int, 0 > pointer;

    EXPECT_NE( nullptr, pointer.get() );
}

TEST( iscool_memory_pimpl, unknown_size )
{
    iscool::memory::pimpl< int, 0 > pointer;

    *pointer = 24;
    EXPECT_EQ( 24, *pointer );
}

TEST( iscool_memory_pimpl, unknown_size_copy )
{
    iscool::memory::pimpl< int, 0 > pointer;
    *pointer = 24;

    iscool::memory::pimpl< int, 0 > copy( pointer );
    *pointer = 42;
    
    EXPECT_EQ( 24, *copy );
    EXPECT_EQ( 42, *pointer );
}

TEST( iscool_memory_pimpl, unknown_size_move )
{
    typedef std::unique_ptr< int > value_type;
    int* value( new int( 24 ) );
    
    iscool::memory::pimpl< value_type, 0 > pointer;
    pointer->reset( value );

    iscool::memory::pimpl< value_type, 0 > moved( std::move( pointer ) );

    EXPECT_EQ( nullptr, pointer->get() );
    EXPECT_EQ( value, moved->get() );

    EXPECT_EQ( 24, **moved );
}

TEST( iscool_memory_pimpl, known_size_auto_allocation )
{
    iscool::memory::pimpl< int, sizeof( int ) > pointer;

    EXPECT_GE( static_cast< void* >( &pointer ),
               static_cast< void* >( pointer.get() ) );
    EXPECT_LE( static_cast< void* >( &pointer - sizeof( int ) ),
               static_cast< void* >( pointer.get() ) );
}

TEST( iscool_memory_pimpl, known_size )
{
    iscool::memory::pimpl< int, sizeof( int ) > pointer;

    *pointer = 24;
    EXPECT_EQ( 24, *pointer );
}

TEST( iscool_memory_pimpl, known_size_copy )
{
    iscool::memory::pimpl< int, sizeof( int ) > pointer;
    *pointer = 24;

    iscool::memory::pimpl< int, sizeof( int ) > copy( pointer );
    
    EXPECT_GE( static_cast< void* >( &copy ),
               static_cast< void* >( copy.get() ) );
    EXPECT_LE( static_cast< void* >( &copy - sizeof( int ) ),
               static_cast< void* >( copy.get() ) );

    *pointer = 42;

    EXPECT_EQ( 24, *copy );
    EXPECT_EQ( 42, *pointer );
}

TEST( iscool_memory_pimpl, known_size_move )
{
    typedef std::unique_ptr< int > value_type;
    
    iscool::memory::pimpl< value_type, sizeof( value_type ) > pointer;
    pointer->reset( new int( 24 ) );

    iscool::memory::pimpl< value_type, sizeof( value_type ) > moved
        ( std::move( pointer ) );

    EXPECT_EQ( nullptr, pointer->get() );

    EXPECT_GE( static_cast< void* >( &moved ),
               static_cast< void* >( moved.get() ) );
    EXPECT_LE( static_cast< void* >( &moved - sizeof( int ) ),
               static_cast< void* >( moved.get() ) );

    EXPECT_EQ( 24, **moved );
}

TEST( iscool_memory_pimpl, unknown_size_constructor_arguments )
{
    struct value_type
    {
    public:
        value_type( int a, const std::string& b, std::vector< int >&& c )
            : a( a ),
              b( b ),
              c( std::move( c ) )
            {}

    public:
        int a;
        std::string b;
        std::vector< int > c;
    };

    iscool::memory::pimpl< value_type, 0 > pointer
        ( 873, "yep", std::vector< int >( { 9, 1 } ) );
    
    EXPECT_EQ( 873, pointer->a );
    EXPECT_EQ( std::string( "yep" ), pointer->b );
    EXPECT_EQ( std::size_t( 2 ), pointer->c.size() );
    EXPECT_EQ( 9, pointer->c[ 0 ] );
    EXPECT_EQ( 1, pointer->c[ 1 ] );
}

TEST( iscool_memory_pimpl, known_size_constructor_arguments )
{
    struct value_type
    {
    public:
        value_type( int a, const std::string& b, std::vector< int >&& c )
            : a( a ),
              b( b ),
              c( std::move( c ) )
            {}

    public:
        int a;
        std::string b;
        std::vector< int > c;
    };

    iscool::memory::pimpl< value_type, sizeof( value_type ) > pointer
        ( 873, "yep", std::vector< int >( { 9, 1 } ) );
    
    EXPECT_EQ( 873, pointer->a );
    EXPECT_EQ( std::string( "yep" ), pointer->b );
    EXPECT_EQ( std::size_t( 2 ), pointer->c.size() );
    EXPECT_EQ( 9, pointer->c[ 0 ] );
    EXPECT_EQ( 1, pointer->c[ 1 ] );
}

TEST( iscool_memory_pimpl, unknown_size_non_copyable_type )
{
    struct value_type
    {
    public:
        explicit value_type( int a )
            : a( a )
            {}

        value_type( const value_type& ) = delete;
        value_type& operator=( const value_type& ) = delete;
        
        value_type( value_type&& that )
            : a( that.a )
        {
            that.a = 0;
        }
        
        value_type& operator=( value_type&& that )
        {
            a = that.a;
            that.a = 0;
            return *this;
        }
        
    public:
        int a;
    };

    iscool::memory::pimpl< value_type, 0 > pointer( 83 );
    EXPECT_EQ( 83, pointer->a );

    iscool::memory::pimpl< value_type, 0 > moved( std::move( pointer ) );
    EXPECT_NE( pointer.get(), moved.get() );

    EXPECT_EQ( 0, pointer->a );
    EXPECT_EQ( 83, moved->a );

    pointer = std::move( moved );
    EXPECT_EQ( 0, moved->a );
    EXPECT_EQ( 83, pointer->a );
}

TEST( iscool_memory_pimpl, known_size_non_copyable_type )
{
    struct value_type
    {
    public:
        explicit value_type( int a )
            : a( a )
            {}

        value_type( const value_type& ) = delete;
        value_type& operator=( const value_type& ) = delete;
        
        value_type( value_type&& that )
            : a( that.a )
        {
            that.a = 0;
        }
        
        value_type& operator=( value_type&& that )
        {
            a = that.a;
            that.a = 0;
            return *this;
        }
        
    public:
        int a;
    };

    iscool::memory::pimpl< value_type, sizeof( value_type ) > pointer( 83 );
    EXPECT_EQ( 83, pointer->a );

    iscool::memory::pimpl< value_type, sizeof( value_type ) > moved
        ( std::move( pointer ) );

    EXPECT_NE( pointer.get(), moved.get() );

    EXPECT_EQ( 0, pointer->a );
    EXPECT_EQ( 83, moved->a );

    pointer = std::move( moved );
    EXPECT_EQ( 0, moved->a );
    EXPECT_EQ( 83, pointer->a );
}

TEST( iscool_memory_pimpl, unknown_size_non_movable_type )
{
    struct value_type
    {
    public:
        explicit value_type( int a )
            : a( a )
            {}

        value_type( value_type&& ) = delete;
        value_type& operator=( value_type&& ) = delete;
        
        value_type( const value_type& that )
            : a( that.a )
        {

        }
        
        value_type& operator=( const value_type& that )
        {
            a = that.a;
            return *this;
        }
        
    public:
        int a;
    };

    iscool::memory::pimpl< value_type, 0 > pointer( 83 );
    EXPECT_EQ( 83, pointer->a );

    iscool::memory::pimpl< value_type, 0 > copy( pointer );
    EXPECT_NE( pointer.get(), copy.get() );

    EXPECT_EQ( 83, pointer->a );
    EXPECT_EQ( 83, copy->a );

    pointer->a = 19;
    EXPECT_EQ( 19, pointer->a );
    EXPECT_EQ( 83, copy->a );
    
    copy = pointer;
    EXPECT_EQ( 19, copy->a );
}

TEST( iscool_memory_pimpl, known_size_non_movable_type )
{
    struct value_type
    {
    public:
        explicit value_type( int a )
            : a( a )
            {}

        value_type( value_type&& ) = delete;
        value_type& operator=( value_type&& ) = delete;
        
        value_type( const value_type& that )
            : a( that.a )
        {

        }
        
        value_type& operator=( const value_type& that )
        {
            a = that.a;
            return *this;
        }
        
    public:
        int a;
    };

    iscool::memory::pimpl< value_type, sizeof( value_type ) > pointer( 83 );
    EXPECT_EQ( 83, pointer->a );

    iscool::memory::pimpl< value_type, sizeof( value_type ) > copy( pointer );
    EXPECT_NE( pointer.get(), copy.get() );
    
    EXPECT_EQ( 83, pointer->a );
    EXPECT_EQ( 83, copy->a );

    pointer->a = 19;
    EXPECT_EQ( 19, pointer->a );
    EXPECT_EQ( 83, copy->a );

    copy = pointer;
    EXPECT_EQ( 19, copy->a );
}

TEST( iscool_memory_pimpl, alignment )
{
    struct value_type
    {
        int a;
    };

    struct with_pimpl
    {
        bool a;
        iscool::memory::pimpl< value_type, sizeof( value_type ) > value;
    } pimpl;

    EXPECT_EQ( 0, std::uintptr_t( pimpl.value.get() ) % alignof( value_type ) );
}
