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
#include "iscool/json/bad_cast.h"
#include "iscool/json/cast_uint8.h"
#include "iscool/json/is_of_type_uint8.h"

#include <lib_json/value.h>

#include <gtest/gtest.h>

TEST( iscool_json_cast, to_uint8 )
{
    const Json::Value value0( 0 );
    EXPECT_EQ
        ( std::uint8_t( 0 ),
          iscool::json::cast< std::uint8_t >( value0 ) );

    const Json::Value value2( 100 );
    EXPECT_EQ
        ( std::uint8_t( 100 ),
          iscool::json::cast< std::uint8_t >( value2 ) );

    const Json::Value value5( std::uint8_t( 255 ) );
    EXPECT_EQ
        ( std::uint8_t( 255 ),
          iscool::json::cast< std::uint8_t >( value5 ) );
}

TEST( iscool_json_cast, is_of_type_uint8 )
{
    const Json::Value value0( 0 );
    EXPECT_TRUE( iscool::json::is_of_type< std::uint8_t >( value0 ) );

    const Json::Value value2( 100 );
    EXPECT_TRUE( iscool::json::is_of_type< std::uint8_t >( value2 ) );

    const Json::Value value5( std::uint8_t( 255 ) );
    EXPECT_TRUE( iscool::json::is_of_type< std::uint8_t >( value5 ) );
}

TEST( iscool_json_cast, is_not_of_type_uint8 )
{
    const Json::Value value;
    EXPECT_FALSE( iscool::json::is_of_type< std::uint8_t >( value ) );

    const Json::Value value0( "10" );
    EXPECT_FALSE( iscool::json::is_of_type< std::uint8_t >( value0 ) );

    const Json::Value value1( true );
    EXPECT_FALSE( iscool::json::is_of_type< std::uint8_t >( value1 ) );

    const Json::Value value2( Json::arrayValue );
    EXPECT_FALSE( iscool::json::is_of_type< std::uint8_t >( value2 ) );

    const Json::Value value3( Json::objectValue );
    EXPECT_FALSE( iscool::json::is_of_type< std::uint8_t >( value3 ) );

    const Json::Value value4( -100 );
    EXPECT_FALSE( iscool::json::is_of_type< std::uint8_t >( value4 ) );

    const Json::Value value5( -123456789 );
    EXPECT_FALSE( iscool::json::is_of_type< std::uint8_t >( value5 ) );

    const Json::Value value6( std::int64_t( -1234567890123456 ) );
    EXPECT_FALSE( iscool::json::is_of_type< std::uint8_t >( value6 ) );

    const Json::Value value7( 5.4f );
    EXPECT_FALSE( iscool::json::is_of_type< std::uint8_t >( value7 ) );
}

TEST( iscool_json_cast, to_uint8_throw )
{
    const Json::Value value;
    EXPECT_THROW
        ( iscool::json::cast< std::uint8_t >( value ),
          iscool::json::bad_cast );

    const Json::Value value0( "10" );
    EXPECT_THROW
        ( iscool::json::cast< std::uint8_t >( value0 ),
          iscool::json::bad_cast );

    const Json::Value value1( true );
    EXPECT_THROW
        ( iscool::json::cast< std::uint8_t >( value1 ),
          iscool::json::bad_cast );

    const Json::Value value2( Json::arrayValue );
    EXPECT_THROW
        ( iscool::json::cast< std::uint8_t >( value2 ),
          iscool::json::bad_cast );

    const Json::Value value3( Json::objectValue );
    EXPECT_THROW
        ( iscool::json::cast< std::uint8_t >( value3 ),
          iscool::json::bad_cast );

    const Json::Value value4( -100 );
    EXPECT_THROW
        ( iscool::json::cast< std::uint8_t >( value4 ),
          iscool::json::bad_cast );

    const Json::Value value5( -123456789 );
    EXPECT_THROW
        ( iscool::json::cast< std::uint8_t >( value5 ),
          iscool::json::bad_cast );

    const Json::Value value6( std::int64_t( -1234567890123456 ) );
    EXPECT_THROW
        ( iscool::json::cast< std::uint8_t >( value6 ),
          iscool::json::bad_cast );

    const Json::Value value7( 5.4f );
    EXPECT_THROW
        ( iscool::json::cast< std::uint8_t >( value7 ),
          iscool::json::bad_cast );
}

TEST( iscool_json_cast, to_uint8_fallback )
{
    EXPECT_EQ( 123, iscool::json::cast< std::uint8_t >( Json::Value(), 123 ) );
    EXPECT_EQ( 24, iscool::json::cast< std::uint8_t >( Json::Value(), 24 ) );
    EXPECT_EQ
        ( std::uint8_t( 255 ),
          iscool::json::cast< std::uint8_t >( Json::Value( 255 ), 23 ) );
}
