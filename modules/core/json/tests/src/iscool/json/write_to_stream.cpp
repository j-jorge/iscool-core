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
#include "iscool/json/write_to_stream.h"

#include "iscool/json/cast_int.h"
#include "iscool/json/cast_string.h"
#include "iscool/json/parse_stream.h"

#include <gtest/gtest.h>

TEST( iscool_json, _write_to_stream )
{
    Json::Value source_value;
    source_value[ "int" ] = 24;
    source_value[ "object" ][ "property" ] = "value";
    source_value[ "array" ][ 0 ] = 10;
    source_value[ "array" ][ 1 ] = 2;
    source_value[ "array" ][ 2 ][ "id" ] = 72;
    source_value[ "array" ][ 3 ] = 1.8;
    
    std::stringstream oss;

    EXPECT_TRUE( iscool::json::write_to_stream( oss, source_value ) );

    const Json::Value result( iscool::json::parse_stream( oss ) );

    EXPECT_EQ( 24, iscool::json::cast< int >( result[ "int" ] ) );
    EXPECT_EQ( "value",
               iscool::json::cast< std::string >
               ( result[ "object" ][ "property" ] ) );

    ASSERT_EQ( Json::ArrayIndex( 4 ), result[ "array" ].size() );
    EXPECT_EQ( 10, iscool::json::cast< int >( result[ "array" ][0] ) );
    EXPECT_EQ( 2, iscool::json::cast< int >( result[ "array" ][1] ) );
    EXPECT_EQ( 72,
                iscool::json::cast< int >( result[ "array" ][2][ "id" ] ) );
    EXPECT_EQ( 1.8f, result[ "array" ][3].asFloat() );
}
