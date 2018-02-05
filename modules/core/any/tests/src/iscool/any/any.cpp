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
#include "iscool/any/any.h"
#include "iscool/any/any.impl.tpp"
#include "iscool/any/declare_visitor_interface.h"
#include "iscool/any/implement_visitor_interface.h"

#include <gtest/gtest.h>

#include <string>

namespace iscool
{
    namespace any
    {
        namespace tests
        {
            struct call_count
            {
                int construct = 0;
                int copy = 0;
                int move = 0;
                int copy_assign = 0;
                int move_assign = 0;
                int destroy = 0;
            };

            class call_counter
            {
            public:
                explicit call_counter( call_count& count );
                call_counter( const call_counter& that );
                call_counter( call_counter&& that );
                ~call_counter();
                
                call_counter& operator=( const call_counter& that );
                call_counter& operator=( call_counter&& that );
                
            private:
                call_count* _count;
            };
            
        }
    }
}

iscool::any::tests::call_counter::call_counter( call_count& count )
    : _count( &count )
{
    ++_count->construct;
}

iscool::any::tests::call_counter::call_counter( const call_counter& that )
    : _count( that._count )
{
    ++_count->copy;
}

iscool::any::tests::call_counter::call_counter( call_counter&& that )
    : _count( that._count )
{
    ++_count->move;
}

iscool::any::tests::call_counter::~call_counter()
{
    ++_count->destroy;
}

iscool::any::tests::call_counter& iscool::any::tests::call_counter::operator=
( const call_counter& that )
{
    _count = that._count;
    ++_count->copy_assign;
    return *this;
}

iscool::any::tests::call_counter& iscool::any::tests::call_counter::operator=
( call_counter&& that )
{
    _count = that._count;
    ++_count->move_assign;
    return *this;
}

TEST( iscool_any, value )
{
    iscool::any::tests::call_count calls;
    iscool::any::tests::call_counter counter( calls );
    
    EXPECT_EQ( 1, calls.construct );
    EXPECT_EQ( 0, calls.copy );
    EXPECT_EQ( 0, calls.move );
    EXPECT_EQ( 0, calls.copy_assign );
    EXPECT_EQ( 0, calls.move_assign );
    EXPECT_EQ( 0, calls.destroy );

    iscool::any::any value_1( counter );

    EXPECT_EQ( 1, calls.construct );
    EXPECT_EQ( 1, calls.copy );
    EXPECT_EQ( 0, calls.move );
    EXPECT_EQ( 0, calls.copy_assign );
    EXPECT_EQ( 0, calls.move_assign );
    EXPECT_EQ( 0, calls.destroy );

    {
        iscool::any::any value_2( value_1 );
        EXPECT_EQ( 1, calls.construct );
        EXPECT_EQ( 2, calls.copy );
        EXPECT_EQ( 0, calls.move );
        EXPECT_EQ( 0, calls.copy_assign );
        EXPECT_EQ( 0, calls.move_assign );
        EXPECT_EQ( 0, calls.destroy );
    }

    EXPECT_EQ( 1, calls.construct );
    EXPECT_EQ( 2, calls.copy );
    EXPECT_EQ( 0, calls.move );
    EXPECT_EQ( 0, calls.copy_assign );
    EXPECT_EQ( 0, calls.move_assign );
    EXPECT_EQ( 1, calls.destroy );
    
    iscool::any::any value_2( std::move( value_1 ) );

    EXPECT_EQ( 1, calls.construct );
    EXPECT_EQ( 2, calls.copy );
    EXPECT_EQ( 0, calls.move );
    EXPECT_EQ( 0, calls.copy_assign );
    EXPECT_EQ( 0, calls.move_assign );
    EXPECT_EQ( 1, calls.destroy );

    value_1 = value_2;

    EXPECT_EQ( 1, calls.construct );
    EXPECT_EQ( 3, calls.copy );
    EXPECT_EQ( 0, calls.move );
    EXPECT_EQ( 0, calls.copy_assign );
    EXPECT_EQ( 0, calls.move_assign );
    EXPECT_EQ( 1, calls.destroy );

    value_2 = std::move( value_1 );

    EXPECT_EQ( 1, calls.construct );
    EXPECT_EQ( 3, calls.copy );
    EXPECT_EQ( 0, calls.move );
    EXPECT_EQ( 0, calls.copy_assign );
    EXPECT_EQ( 0, calls.move_assign );
    EXPECT_EQ( 2, calls.destroy );
}

TEST( iscool_any, get )
{
    iscool::any::any value_1;

    EXPECT_EQ( nullptr, value_1.get< int >() );
    EXPECT_EQ( nullptr, value_1.get< std::string >() );

    value_1 = 18;
    
    EXPECT_NE( nullptr, value_1.get< int >() );
    EXPECT_EQ( nullptr, value_1.get< std::string >() );

    {
        iscool::any::any value_2( value_1 );
        EXPECT_NE( value_1.get< int >(), value_2.get< int >() );
        EXPECT_EQ( *value_1.get< int >(), *value_2.get< int >() );
    }

    iscool::any::any value_2( std::move( value_1 ) );

    EXPECT_EQ( nullptr, value_1.get< int >() );
    EXPECT_EQ( 18, *value_2.get< int >() );

    value_1 = value_2;

    EXPECT_NE( value_1.get< int >(), value_2.get< int >() );
    EXPECT_EQ( *value_1.get< int >(), *value_2.get< int >() );

    value_2 = std::move( value_1 );

    EXPECT_EQ( nullptr, value_1.get< int >() );
    EXPECT_EQ( 18, *value_2.get< int >() );

    value_1 = std::string( "ok" );
    
    EXPECT_EQ( "ok", *value_1.get< std::string >() );
    EXPECT_EQ( 18, *value_2.get< int >() );

    std::swap( value_1, value_2 );

    EXPECT_EQ( 18, *value_1.get< int >() );
    EXPECT_EQ( "ok", *value_2.get< std::string >() );
}

namespace iscool
{
    namespace any
    {
        namespace tests
        {
            class any_test_int_visitor
            {
            public:
                ic_any_declare_visitor_interface
                (
                    ( int )
                );

            public:
                int calls = 0;
                int value;
            };

            class any_test_string_visitor
            {
            public:
                ic_any_declare_visitor_interface
                (
                    ( std::string )
                );

            public:
                int calls = 0;
                std::string value;
            };
            
            class any_test_int_string_visitor
            {
            public:
                ic_any_declare_visitor_interface
                (
                    ( int )
                    ( std::string )
                );

            public:
                int int_calls = 0;
                int int_value;

                int string_calls = 0;
                std::string string_value;
            };
        }
    }
}

ic_any_implement_visitor_interface( iscool::any::tests::any_test_int_visitor );
ic_any_implement_visitor_interface
( iscool::any::tests::any_test_string_visitor );
ic_any_implement_visitor_interface
( iscool::any::tests::any_test_int_string_visitor );

void iscool::any::tests::any_test_int_visitor::operator()( const int& v )
{
    ++calls;
    value = v;
}

void iscool::any::tests::any_test_string_visitor::operator()
( const std::string& v )
{
    ++calls;
    value = v;
}

void iscool::any::tests::any_test_int_string_visitor::operator()
( const int& v )
{
    ++int_calls;
    int_value = v;
}

void iscool::any::tests::any_test_int_string_visitor::operator()
( const std::string& v )
{
    ++string_calls;
    string_value = v;
}

TEST( iscool_any, visit )
{
    const iscool::any::any int_value( 24 );
    const iscool::any::any string_value( std::string( "ok" ) );

    iscool::any::tests::any_test_int_visitor int_visitor;
    iscool::any::tests::any_test_string_visitor string_visitor;

    {
        int_value.visit< iscool::any::tests::any_test_int_visitor& >
            ( int_visitor );
    
        EXPECT_EQ( 1, int_visitor.calls );
        EXPECT_EQ( 24, int_visitor.value );

        int_value.visit< iscool::any::tests::any_test_string_visitor& >
            ( string_visitor );
    
        EXPECT_EQ( 0, string_visitor.calls );
    }

    {
        string_value.visit< iscool::any::tests::any_test_string_visitor& >
            ( string_visitor );
    
        EXPECT_EQ( 1, string_visitor.calls );
        EXPECT_EQ( "ok", string_visitor.value );

        string_value.visit< iscool::any::tests::any_test_int_visitor& >
            ( int_visitor );
    
        EXPECT_EQ( 1, int_visitor.calls );
    }

    {
        iscool::any::tests::any_test_int_string_visitor int_string_visitor;
    
        int_value.visit< iscool::any::tests::any_test_int_string_visitor& >
            ( int_string_visitor );
    
        EXPECT_EQ( 1, int_string_visitor.int_calls );
        EXPECT_EQ( 24, int_string_visitor.int_value );
        EXPECT_EQ( 0, int_string_visitor.string_calls );
        EXPECT_EQ( "", int_string_visitor.string_value );
    
        string_value.visit< iscool::any::tests::any_test_int_string_visitor& >
            ( int_string_visitor );
    
        EXPECT_EQ( 1, int_string_visitor.int_calls );
        EXPECT_EQ( 24, int_string_visitor.int_value );
        EXPECT_EQ( 1, int_string_visitor.string_calls );
        EXPECT_EQ( "ok", int_string_visitor.string_value );
    }
}
