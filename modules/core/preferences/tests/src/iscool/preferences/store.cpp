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
#include "iscool/preferences/store.h"

#include "iscool/schedule/manual_scheduler.h"
#include "iscool/schedule/setup.h"

#include <thread>

#include <gtest/gtest.h>

class iscool_preferences_store_test:
    public ::testing::Test
{
public:
    iscool_preferences_store_test();
    ~iscool_preferences_store_test();

protected:
    typedef
    boost::function< void( iscool::preferences::property_map ) > save_function;
    
protected:
    void wait( std::chrono::milliseconds delay );

protected:
    iscool::preferences::property_map _initial_values;
    save_function _empty_save_function;

    iscool::preferences::property_map _values_to_save;
    save_function _copy_values_save_function;
    
private:
    iscool::schedule::manual_scheduler _scheduler;
};

iscool_preferences_store_test::iscool_preferences_store_test()
{
    iscool::schedule::initialize( _scheduler.get_delayed_call_delegate() );

    _initial_values.set< int >( "int", 24 );

    _empty_save_function =
        []( iscool::preferences::property_map ) -> void
        {
            ASSERT_TRUE( false );
        };

    _copy_values_save_function =
        [ this ]( iscool::preferences::property_map values ) -> void
        {
            _values_to_save = values;
        };
}

iscool_preferences_store_test::~iscool_preferences_store_test()
{
    iscool::schedule::finalize();
}

void iscool_preferences_store_test::wait( std::chrono::milliseconds delay )
{
    if ( delay != std::chrono::milliseconds::zero() )
        std::this_thread::sleep_for( delay );
    
    _scheduler.update_interval( delay );
}

TEST_F( iscool_preferences_store_test, initial_values )
{
    iscool::preferences::store store
        ( std::chrono::milliseconds::zero(), _initial_values,
          _empty_save_function );

    EXPECT_EQ( 24, store.get_value( "int", 0 ) );
    EXPECT_EQ( 0, store.get_value( "nope", 0 ) );
    EXPECT_FALSE( store.is_dirty() );
}

TEST_F( iscool_preferences_store_test, set_value )
{
    iscool::preferences::store store
        ( std::chrono::milliseconds::zero(), _initial_values,
          _empty_save_function );

    EXPECT_EQ( 24, store.get_value( "int", 0 ) );
    store.set_value( "int", 88 );
    EXPECT_EQ( 88, store.get_value( "int", 0 ) );
    EXPECT_TRUE( store.is_dirty() );

    store.set_value( "string", std::string( "some string" ) );
    EXPECT_EQ( "some string", store.get_value< std::string >( "string", "" ) );
}

TEST_F( iscool_preferences_store_test, set_value_schedules_save )
{
    iscool::preferences::store store
        ( std::chrono::milliseconds::zero(), _initial_values,
          _copy_values_save_function );

    store.set_value( "int", 83 );
    EXPECT_TRUE( _values_to_save.empty() );

    wait( std::chrono::milliseconds::zero() );
    EXPECT_TRUE( store.is_dirty() );
    EXPECT_FALSE( _values_to_save.empty() );
    
    EXPECT_TRUE( _values_to_save.has< int >( "int" ) );
    EXPECT_EQ( 83, *_values_to_save.get< int >( "int" ) );
}

TEST_F( iscool_preferences_store_test, save_with_delay )
{
    iscool::preferences::store store
        ( std::chrono::milliseconds( 10 ), _initial_values,
          _copy_values_save_function );

    store.set_value( "int", 83 );
    EXPECT_TRUE( _values_to_save.empty() );

    wait( std::chrono::milliseconds( 5 ) );
    EXPECT_TRUE( _values_to_save.empty() );
    
    wait( std::chrono::milliseconds( 5 ) );
    wait( std::chrono::milliseconds( 0 ) );
    EXPECT_TRUE( store.is_dirty() );
    EXPECT_FALSE( _values_to_save.empty() );
    
    EXPECT_TRUE( _values_to_save.has< int >( "int" ) );
    EXPECT_EQ( 83, *_values_to_save.get< int >( "int" ) );
}

TEST_F( iscool_preferences_store_test, set_value_during_save )
{
    iscool::preferences::store store
        ( std::chrono::milliseconds::zero(), _initial_values,
          _copy_values_save_function );

    store.set_value( "int", 83 );
    wait( std::chrono::milliseconds::zero() );

    EXPECT_TRUE( store.is_dirty() );
    EXPECT_EQ( 83, store.get_value( "int", 0 ) );
    
    store.set_value( "int", 24 );
    EXPECT_EQ( 24, store.get_value( "int", 0 ) );
    wait( std::chrono::milliseconds::zero() );

    EXPECT_TRUE( store.is_dirty() );
    EXPECT_TRUE( _values_to_save.has< int >( "int" ) );
    EXPECT_EQ( 83, *_values_to_save.get< int >( "int" ) );
}

TEST_F( iscool_preferences_store_test, confirm_save )
{
    iscool::preferences::store store
        ( std::chrono::milliseconds::zero(), _initial_values,
          _copy_values_save_function );

    store.set_value( "int", 83 );
    wait( std::chrono::milliseconds::zero() );

    EXPECT_TRUE( store.is_dirty() );
    EXPECT_TRUE( _values_to_save.has< int >( "int" ) );
    EXPECT_EQ( 83, *_values_to_save.get< int >( "int" ) );

    store.set_value( "int", 24 );

    _values_to_save.clear();
    store.confirm_save();
    EXPECT_TRUE( store.is_dirty() );
    
    wait( std::chrono::milliseconds::zero() );

    EXPECT_TRUE( _values_to_save.has< int >( "int" ) );
    EXPECT_EQ( 24, *_values_to_save.get< int >( "int" ) );

    store.confirm_save();
    EXPECT_FALSE( store.is_dirty() );
}

TEST_F( iscool_preferences_store_test, save_error )
{
    iscool::preferences::store store
        ( std::chrono::milliseconds::zero(), _initial_values,
          _copy_values_save_function );

    store.set_value( "int", 83 );
    wait( std::chrono::milliseconds::zero() );

    EXPECT_TRUE( _values_to_save.has< int >( "int" ) );
    EXPECT_EQ( 83, *_values_to_save.get< int >( "int" ) );

    store.set_value( "bool", true );

    _values_to_save.clear();
    store.save_error();

    wait( std::chrono::milliseconds::zero() );

    EXPECT_FALSE( _values_to_save.empty() );

    EXPECT_TRUE( _values_to_save.has< int >( "int" ) );
    EXPECT_EQ( 83, *_values_to_save.get< int >( "int" ) );

    EXPECT_TRUE( store.is_dirty() );
    EXPECT_TRUE( _values_to_save.has< bool >( "bool" ) );
    EXPECT_EQ( true, *_values_to_save.get< bool >( "bool" ) );
}

TEST_F( iscool_preferences_store_test, flush )
{
    iscool::preferences::store store
        ( std::chrono::milliseconds( 5 ), _initial_values,
          _copy_values_save_function );

    store.set_value( "int", 83 );
    store.flush();
    wait( std::chrono::milliseconds::zero() );
    
    EXPECT_TRUE( _values_to_save.has< int >( "int" ) );
    EXPECT_EQ( 83, *_values_to_save.get< int >( "int" ) );
}

TEST_F( iscool_preferences_store_test, flush_in_save )
{
    iscool::preferences::store store
        ( std::chrono::milliseconds( 5 ), _initial_values,
          _copy_values_save_function );

    store.set_value( "int", 83 );
    wait( std::chrono::milliseconds( 5 ) );

    EXPECT_FALSE( _values_to_save.empty() );

    store.set_value( "bool", true );
    store.flush();
    wait( std::chrono::milliseconds::zero() );
    
    EXPECT_TRUE( _values_to_save.has< int >( "int" ) );
    EXPECT_EQ( 83, *_values_to_save.get< int >( "int" ) );
    
    EXPECT_TRUE( _values_to_save.has< bool >( "bool" ) );
    EXPECT_EQ( true, *_values_to_save.get< bool >( "bool" ) );
}
