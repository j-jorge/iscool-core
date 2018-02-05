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
#include "iscool/json/cast_uint.h"
#include "iscool/json/is_of_type_uint.h"

#include <lib_json/value.h>

#include "gtest/gtest.h"

TEST( iscool_json_cast, to_uint )
{
    Json::Value value0( 0u );
    EXPECT_EQ( 0u, iscool::json::cast< unsigned int >( value0 ) );

    Json::Value value1( 100 );
    EXPECT_EQ( 100u, iscool::json::cast< unsigned int >( value1 ) );

    Json::Value value2( 10000 );
    EXPECT_EQ( 10000u, iscool::json::cast< unsigned int >( value2 ) );

    Json::Value value3( std::uint64_t( 123456789 ) );
    EXPECT_EQ( 123456789u, iscool::json::cast< unsigned int >( value3 ) );
}

TEST( iscool_json_cast, is_of_type_uint )
{
    Json::Value value0( 0u );
    EXPECT_TRUE( iscool::json::is_of_type< unsigned int >( value0 ) );

    Json::Value value1( 100 );
    EXPECT_TRUE( iscool::json::is_of_type< unsigned int >( value1 ) );

    Json::Value value2( 10000 );
    EXPECT_TRUE( iscool::json::is_of_type< unsigned int >( value2 ) );

    Json::Value value3( std::uint64_t( 123456789 ) );
    EXPECT_TRUE( iscool::json::is_of_type< unsigned int >( value3 ) );
}

TEST( iscool_json_cast, is_not_of_type_uint )
{
    Json::Value value;  
    EXPECT_FALSE( iscool::json::is_of_type< unsigned int >( value ) );

    Json::Value value0( "10" );
    EXPECT_FALSE( iscool::json::is_of_type< unsigned int >( value0 ) );

    Json::Value value1( 5.4f );
    EXPECT_FALSE( iscool::json::is_of_type< unsigned int >( value1 ) );

    Json::Value value2( true );
    EXPECT_FALSE( iscool::json::is_of_type< unsigned int >( value2 ) );

    Json::Value value3( -10 );
    EXPECT_FALSE( iscool::json::is_of_type< unsigned int >( value3 ) );

    Json::Value value4( Json::arrayValue );
    EXPECT_FALSE( iscool::json::is_of_type< unsigned int >( value4 ) );

    Json::Value value5( Json::objectValue );
    EXPECT_FALSE( iscool::json::is_of_type< unsigned int >( value5 ) );
}

TEST( iscool_json_cast, to_uint_throw )
{
    Json::Value value;  
    EXPECT_THROW( iscool::json::cast< unsigned int >( value ),
                  iscool::json::bad_cast );

    Json::Value value0( "10" );
    EXPECT_THROW( iscool::json::cast< unsigned int >( value0 ),
                  iscool::json::bad_cast );

    Json::Value value1( 5.4f );
    EXPECT_THROW( iscool::json::cast< unsigned int >( value1 ),
                  iscool::json::bad_cast );

    Json::Value value2( true );
    EXPECT_THROW( iscool::json::cast< unsigned int >( value2 ),
                  iscool::json::bad_cast );

    Json::Value value3( -10 );
    EXPECT_THROW( iscool::json::cast< unsigned int >( value3 ),
                  iscool::json::bad_cast );

    Json::Value value4( Json::arrayValue );
    EXPECT_THROW( iscool::json::cast< unsigned int >( value4 ),
                  iscool::json::bad_cast );

    Json::Value value5( Json::objectValue );
    EXPECT_THROW( iscool::json::cast< unsigned int >( value5 ),
                  iscool::json::bad_cast );
}

TEST( iscool_json_cast, to_uint_fallback )
{
    EXPECT_EQ( 24, iscool::json::cast< unsigned int >( Json::Value(), 24 ) );
    EXPECT_EQ( 42, iscool::json::cast< unsigned int >( Json::Value(), 42 ) );
    EXPECT_EQ( 42, iscool::json::cast< unsigned int >( Json::Value( 42 ), 2 ) );
}
