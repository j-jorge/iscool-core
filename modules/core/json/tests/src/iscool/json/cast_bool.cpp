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
#include "iscool/json/cast_bool.h"
#include "iscool/json/is_of_type_bool.h"

#include <json/value.h>

#include "gtest/gtest.h"

TEST( iscool_json_cast, to_bool )
{
    Json::Value value0( true );
    EXPECT_TRUE( iscool::json::cast< bool >( value0 ) );

    Json::Value value1( false );
    EXPECT_FALSE( iscool::json::cast< bool >( value1 ) );
}

TEST( iscool_json_cast, is_of_type_bool )
{
    Json::Value value0( true );
    EXPECT_TRUE( iscool::json::is_of_type< bool >( value0 ) );

    Json::Value value1( false );
    EXPECT_TRUE( iscool::json::is_of_type< bool >( value1 ) );
}

TEST( iscool_json_cast, is_not_of_type_bool )
{
    Json::Value value;
    EXPECT_FALSE( iscool::json::is_of_type< bool >( value ) );

    Json::Value value0( "10" );
    EXPECT_FALSE( iscool::json::is_of_type< bool >( value0 ) );

    Json::Value value1( std::uint64_t( 0x123456789abcdef ) );
    EXPECT_FALSE( iscool::json::is_of_type< bool >( value1 ) );

    Json::Value value2( Json::arrayValue );
    EXPECT_FALSE( iscool::json::is_of_type< bool >( value2 ) );

    Json::Value value3( Json::objectValue );
    EXPECT_FALSE( iscool::json::is_of_type< bool >( value3 ) );

    Json::Value value4( 5.4f );
    EXPECT_FALSE( iscool::json::is_of_type< bool >( value4 ) );

    Json::Value value5( -10 );
    EXPECT_FALSE( iscool::json::is_of_type< bool >( value5 ) );
}

TEST( iscool_json_cast, to_bool_throw )
{
    Json::Value value;
    EXPECT_THROW( iscool::json::cast< bool >( value ), iscool::json::bad_cast );

    Json::Value value0( "10" );
    EXPECT_THROW( iscool::json::cast< bool >( value0 ),
                  iscool::json::bad_cast );

    Json::Value value1( std::uint64_t( 0x123456789abcdef ) );
    EXPECT_THROW( iscool::json::cast< bool >( value1 ),
                  iscool::json::bad_cast );

    Json::Value value2( Json::arrayValue );
    EXPECT_THROW( iscool::json::cast< bool >( value2 ),
                  iscool::json::bad_cast );

    Json::Value value3( Json::objectValue );
    EXPECT_THROW( iscool::json::cast< bool >( value3 ),
                  iscool::json::bad_cast );

    Json::Value value4( 5.4f );
    EXPECT_THROW( iscool::json::cast< bool >( value4 ),
                  iscool::json::bad_cast );

    Json::Value value5( -10 );
    EXPECT_THROW( iscool::json::cast< bool >( value5 ),
                  iscool::json::bad_cast );
}

TEST( iscool_json_cast, to_bool_fallback )
{
    EXPECT_TRUE( iscool::json::cast< bool >( Json::Value(), true ) );
    EXPECT_FALSE( iscool::json::cast< bool >( Json::Value(), false ) );
    EXPECT_TRUE( iscool::json::cast< bool >( Json::Value( true), false ) );
}
