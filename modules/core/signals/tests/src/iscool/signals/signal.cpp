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
#include "iscool/signals/implement_signal.h"

#include <gtest/gtest.h>

TEST( iscool_signals_signal, initially_empty )
{
    iscool::signals::signal< void() > signal;
    EXPECT_TRUE( signal.empty() );
}

TEST( iscool_signals_signal, connect )
{
    iscool::signals::signal< void() > signal;

    bool called( false );
    signal.connect
        ( [ &called ]() -> void
          {
              called = true;
          } );

    EXPECT_FALSE( signal.empty() );
    
    signal();
    EXPECT_TRUE( called );
}

TEST( iscool_signals_signal, disconnect_all_slots )
{
    iscool::signals::signal< void() > signal;

    bool called( false );
    signal.connect
        ( [ &called ]() -> void
          {
              called = true;
          } );

    signal.disconnect_all_slots();
    signal();
    EXPECT_FALSE( called );
}

TEST( iscool_signals_signal, call_order )
{
    iscool::signals::signal< void() > signal;

    std::size_t calls( 0 );
    std::size_t first_call( 0 );
    signal.connect
        ( [ &calls, &first_call ]() -> void
          {
              ++calls;
              first_call = calls;
          } );
    
    std::size_t second_call( 0 );
    signal.connect
        ( [ &calls, &second_call ]() -> void
          {
              ++calls;
              second_call = calls;
          } );

    signal();
    EXPECT_EQ( std::size_t( 1 ), first_call );
    EXPECT_EQ( std::size_t( 2 ), second_call );
}

TEST( iscool_signals_signal, connect_while_triggered )
{
    iscool::signals::signal< void() > signal;

    bool called( false );
    auto set_call
        ( [ &called ]() -> void
          {
              called = true;
          } );
    
    signal.connect
        ( [ &signal, set_call ]() -> void
          {
              signal.connect( set_call );
          } );

    signal();
    EXPECT_FALSE( called );

    signal();
    EXPECT_TRUE( called );
}

TEST( iscool_signals_signal, disconnect_while_triggered )
{
    iscool::signals::signal< void() > signal;

    bool called_1( false );
    iscool::signals::connection connection;
    
    signal.connect
        ( [ &called_1, &connection ]() -> void
          {
              called_1 = true;
              connection.disconnect();
          } );

    bool called_2( false );
    connection =
        signal.connect
        ( [ &called_2 ]() -> void
          {
              called_2 = true;
          } );
    
    signal();
    EXPECT_TRUE( called_1 );
    EXPECT_FALSE( called_2 );
}

TEST( iscool_signals_signal, swap_0_0 )
{
    iscool::signals::signal< void() > signal;
    iscool::signals::signal< void() > signal_alt;

    signal.swap( signal_alt );
    EXPECT_TRUE( signal.empty() );
    EXPECT_TRUE( signal_alt.empty() );
}

TEST( iscool_signals_signal, swap_0_1 )
{
    iscool::signals::signal< void() > signal;

    bool called( false );
    signal.connect
        ( [ &called ]() -> void
          {
              called = true;
          } );

    iscool::signals::signal< void() > signal_alt;
    signal_alt.swap( signal );
    
    signal();
    EXPECT_FALSE( called );

    signal_alt();
    EXPECT_TRUE( called );
}

TEST( iscool_signals_signal, swap_0_n )
{
    iscool::signals::signal< void() > signal;

    bool called_1( false );
    signal.connect
        ( [ &called_1 ]() -> void
          {
              called_1 = true;
          } );

    bool called_2( false );
    signal.connect
        ( [ &called_2 ]() -> void
          {
              called_2 = true;
          } );

    iscool::signals::signal< void() > signal_alt;
    signal_alt.swap( signal );
    
    signal();
    EXPECT_FALSE( called_1 );
    EXPECT_FALSE( called_2 );

    signal_alt();
    EXPECT_TRUE( called_1 );
    EXPECT_TRUE( called_2 );
}

TEST( iscool_signals_signal, swap_1_1 )
{
    iscool::signals::signal< void() > signal;

    bool called( false );
    signal.connect
        ( [ &called ]() -> void
          {
              called = true;
          } );

    iscool::signals::signal< void() > signal_alt;

    bool called_alt( false );
    signal_alt.connect
        ( [ &called_alt ]() -> void
          {
              called_alt = true;
          } );

    signal_alt.swap( signal );
    
    signal();
    EXPECT_FALSE( called );
    EXPECT_TRUE( called_alt );

    called_alt = false;
    signal_alt();
    
    EXPECT_TRUE( called );
    EXPECT_FALSE( called_alt );
}

TEST( iscool_signals_signal, swap_1_n )
{
    iscool::signals::signal< void() > signal;

    bool called( false );
    signal.connect
        ( [ &called ]() -> void
          {
              called = true;
          } );

    iscool::signals::signal< void() > signal_alt;

    bool called_alt_1( false );
    signal_alt.connect
        ( [ &called_alt_1 ]() -> void
          {
              called_alt_1 = true;
          } );

    bool called_alt_2( false );
    signal_alt.connect
        ( [ &called_alt_2 ]() -> void
          {
              called_alt_2 = true;
          } );

    signal_alt.swap( signal );
    
    signal();
    EXPECT_FALSE( called );
    EXPECT_TRUE( called_alt_1 );
    EXPECT_TRUE( called_alt_2 );

    called_alt_1 = false;
    called_alt_2 = false;
    signal_alt();
    
    EXPECT_TRUE( called );
    EXPECT_FALSE( called_alt_1 );
    EXPECT_FALSE( called_alt_2 );
}

TEST( iscool_signals_signal, swap_n_n )
{
    iscool::signals::signal< void() > signal;

    bool called_1( false );
    signal.connect
        ( [ &called_1 ]() -> void
          {
              called_1 = true;
          } );

    bool called_2( false );
    signal.connect
        ( [ &called_2 ]() -> void
          {
              called_2 = true;
          } );

    iscool::signals::signal< void() > signal_alt;

    bool called_alt_1( false );
    signal_alt.connect
        ( [ &called_alt_1 ]() -> void
          {
              called_alt_1 = true;
          } );

    bool called_alt_2( false );
    signal_alt.connect
        ( [ &called_alt_2 ]() -> void
          {
              called_alt_2 = true;
          } );

    signal_alt.swap( signal );
    
    signal();
    EXPECT_FALSE( called_1 );
    EXPECT_FALSE( called_2 );
    EXPECT_TRUE( called_alt_1 );
    EXPECT_TRUE( called_alt_2 );

    called_alt_1 = false;
    called_alt_2 = false;
    signal_alt();
    
    EXPECT_TRUE( called_1 );
    EXPECT_TRUE( called_2 );
    EXPECT_FALSE( called_alt_1 );
    EXPECT_FALSE( called_alt_2 );
}

TEST( iscool_signals_signal, swap_while_triggered )
{
    iscool::signals::signal< void() > signal;

    int calls_1( 0 );
    signal.connect
        ( [ &calls_1 ]() -> void
          {
              ++calls_1;
          } );

    int calls_2( 0 );
    signal.connect
        ( [ &calls_2 ]() -> void
          {
              ++calls_2;
          } );

    iscool::signals::signal< void() > signal_alt;

    signal_alt.connect
        ( [ &signal_alt, &signal ]() -> void
          {
              signal_alt.swap( signal );
          } );
    
    int calls_alt( 0 );
    signal_alt.connect
        ( [ &calls_alt ]() -> void
          {
              ++calls_alt;
          } );
    
    signal_alt();
    EXPECT_EQ( 0, calls_1 );
    EXPECT_EQ( 0, calls_2 );
    EXPECT_EQ( 1, calls_alt );

    signal_alt();
    EXPECT_EQ( 1, calls_1 );
    EXPECT_EQ( 1, calls_2 );
    EXPECT_EQ( 1, calls_alt );
}

TEST( iscool_signals_signal, argument )
{
    iscool::signals::signal< void( int ) > signal;

    int arg( 0 );
    signal.connect
        ( [ &arg ]( int v ) -> void
          {
              arg = v;
          } );

    signal( 24 );
    EXPECT_EQ( 24, arg );
}

TEST( iscool_signals_signal, recursive )
{
    iscool::signals::signal< void( int ) > signal;

    int calls( 0 );
    signal.connect
        ( [ &calls, &signal ]( int v ) -> void
          {
              ++calls;

              if ( v > 0 )
                  signal( v - 1 );
          } );

    signal( 3 );
    EXPECT_EQ( 4, calls );
}

TEST( iscool_signals_signal, connections_of_swapped_signals )
{
    iscool::signals::signal< void() > signal_1;
    bool called_1( false );
    const iscool::signals::connection connection_1
        ( signal_1.connect
          ( [ &called_1 ]() -> void
            {
                called_1 = true;
            } ) );

    iscool::signals::signal< void() > signal_2;
    bool called_2( false );
    const iscool::signals::connection connection_2
        ( signal_2.connect
          ( [ &called_2 ]() -> void
            {
                called_2 = true;
            } ) );

    signal_1.swap( signal_2 );
    signal_1.disconnect_all_slots();

    EXPECT_TRUE( signal_1.empty() );
    EXPECT_FALSE( signal_2.empty() );

    EXPECT_TRUE( connection_1.connected() );
    EXPECT_FALSE( connection_2.connected() );

    signal_2();

    EXPECT_TRUE( called_1 );
    EXPECT_FALSE( called_2 );
}

class dummy_class_with_signal
{
    DECLARE_SIGNAL( void( int ), int, _int );
    DECLARE_VOID_SIGNAL( void, _void );

public:
    dummy_class_with_signal();
    void trigger_int( int i ) const;
    void trigger_void() const;
};

IMPLEMENT_SIGNAL( dummy_class_with_signal, int, _int );
IMPLEMENT_SIGNAL( dummy_class_with_signal, void, _void );

dummy_class_with_signal::dummy_class_with_signal()
{
}
    
void dummy_class_with_signal::trigger_int( int i ) const
{
    _int( i );
}

void dummy_class_with_signal::trigger_void() const
{
    _void();
}

TEST( iscool_signals_signal, declare_macro )
{
    const dummy_class_with_signal dummy;

    int int_arg( 0 );
    dummy.connect_to_int
        ( [ &int_arg ]( int i ) -> void
          {
              int_arg = i;
          } );

    dummy.trigger_int( 843 );
    EXPECT_EQ( 843, int_arg );
    
    bool void_called( false );
    dummy.connect_to_void
        ( [ &void_called ]() -> void
          {
              void_called = true;
          } );

    dummy.trigger_void();
    EXPECT_TRUE( void_called );
}

template< typename T >
class dummy_template_class_with_signal
{
    DECLARE_SIGNAL_IN_TEMPLATE( void( T ), typed, _typed );
    DECLARE_VOID_SIGNAL( void, _void );

public:
    dummy_template_class_with_signal();
    void trigger_typed( T value  ) const;
    void trigger_void() const;
};

template< typename T >
IMPLEMENT_SIGNAL( dummy_template_class_with_signal< T >, typed, _typed );
template< typename T >
IMPLEMENT_SIGNAL( dummy_template_class_with_signal< T >, void, _void );

template< typename T >
dummy_template_class_with_signal< T >::dummy_template_class_with_signal()
{
}
    
template< typename T >
void dummy_template_class_with_signal< T >::trigger_typed( T value ) const
{
    _typed( value );
}

template< typename T >
void dummy_template_class_with_signal< T >::trigger_void() const
{
    _void();
}

TEST( iscool_signals_signal, declare_macro_template )
{
    const dummy_template_class_with_signal< int > dummy;

    int int_arg( 0 );
    dummy.connect_to_typed
        ( [ &int_arg ]( int i ) -> void
          {
              int_arg = i;
          } );

    dummy.trigger_typed( 843 );
    EXPECT_EQ( 843, int_arg );
    
    bool void_called( false );
    dummy.connect_to_void
        ( [ &void_called ]() -> void
          {
              void_called = true;
          } );

    dummy.trigger_void();
    EXPECT_TRUE( void_called );
}
