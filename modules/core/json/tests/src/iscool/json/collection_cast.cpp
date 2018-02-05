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
#include "iscool/json/cast_array.h"
#include "iscool/json/cast_int.h"
#include "iscool/json/cast_string.h"
#include "iscool/json/cast_vector.h"
#include "iscool/json/collection_cast.h"

#include "gtest/gtest.h"

TEST( iscool_json_collection_cast, vector )
{
    struct s
    {
        int a;
        std::string b;
    };

    auto custom_cast
        ( []( const Json::Value& entry ) -> s
          {
              s result;
              result.a = iscool::json::cast< int >( entry[ "a" ] );
              result.b = iscool::json::cast< std::string >( entry[ "b" ] );
              return result;
          } );

    Json::Value input;
    input[ 0 ][ "a" ] = Json::Value( 1 );
    input[ 0 ][ "b" ] = Json::Value( "yep" );
    input[ 1 ][ "a" ] = Json::Value( 94 );
    input[ 1 ][ "b" ] = Json::Value( "great" );
    
    const std::vector< s > result
        ( iscool::json::collection_cast< std::vector< s > >
          ( input, custom_cast ) );
    
    EXPECT_EQ( std::size_t( 2 ), result.size() );
    
    EXPECT_EQ( 1, result[ 0 ].a );
    EXPECT_EQ( "yep", result[ 0 ].b );
    EXPECT_EQ( 94, result[ 1 ].a );
    EXPECT_EQ( "great", result[ 1 ].b );
}

TEST( iscool_json_collection_cast, vector_fail )
{
    struct s
    {
        int a;
        std::string b;
    };

    auto custom_cast
        ( []( const Json::Value& entry ) -> s
          {
              s result;
              result.a = iscool::json::cast< int >( entry[ "a" ] );
              result.b = iscool::json::cast< std::string >( entry[ "b" ] );
              return result;
          } );

    Json::Value input;
    input[ 0 ][ "a" ] = Json::Value( 1 );
    input[ 0 ][ "b" ] = Json::Value( "yep" );
    input[ 1 ][ "a" ] = Json::Value( 94 );
    input[ 1 ][ "b" ] = Json::Value( "great" );
    input[ 2 ][ "b" ] = Json::Value();
    
    EXPECT_THROW
        ( iscool::json::collection_cast< std::vector< s > >
          ( input, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< std::vector< s > >
          ( Json::objectValue, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< std::vector< s > >
          ( Json::realValue, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< std::vector< s > >
          ( Json::intValue, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< std::vector< s > >
          ( Json::booleanValue, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< std::vector< s > >
          ( Json::nullValue, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< std::vector< s > >
          ( Json::uintValue, custom_cast ),
          iscool::json::bad_cast );
}

TEST( iscool_json_collection_cast, vector_default_cast )
{
    Json::Value input;
    input[ 0 ] = Json::Value( "yep" );
    input[ 1 ] = Json::Value( "great" );
    
    const std::vector< std::string > result
        ( iscool::json::collection_cast< std::vector< std::string > >
          ( input ) );
    
    EXPECT_EQ( std::size_t( 2 ), result.size() );
    
    EXPECT_EQ( "yep", result[ 0 ] );
    EXPECT_EQ( "great", result[ 1 ] );
}

TEST( iscool_json_collection_cast, array )
{
    struct s
    {
        int a;
        std::string b;
    };

    auto custom_cast
        ( []( const Json::Value& entry ) -> s
          {
              s result;
              result.a = iscool::json::cast< int >( entry[ "a" ] );
              result.b = iscool::json::cast< std::string >( entry[ "b" ] );
              return result;
          } );

    Json::Value input;
    input[ 0 ][ "a" ] = Json::Value( 1 );
    input[ 0 ][ "b" ] = Json::Value( "yep" );
    input[ 1 ][ "a" ] = Json::Value( 94 );
    input[ 1 ][ "b" ] = Json::Value( "great" );

    typedef std::array< s, 2 > array_t;
    const array_t result
        ( iscool::json::collection_cast< array_t >( input, custom_cast ) );
    
    EXPECT_EQ( 1, result[ 0 ].a );
    EXPECT_EQ( "yep", result[ 0 ].b );
    EXPECT_EQ( 94, result[ 1 ].a );
    EXPECT_EQ( "great", result[ 1 ].b );
}

TEST( iscool_json_collection_cast, array_fail )
{
    struct s
    {
        int a;
        std::string b;
    };

    auto custom_cast
        ( []( const Json::Value& entry ) -> s
          {
              s result;
              result.a = iscool::json::cast< int >( entry[ "a" ] );
              result.b = iscool::json::cast< std::string >( entry[ "b" ] );
              return result;
          } );

    Json::Value input;
    input[ 0 ][ "a" ] = Json::Value( 1 );
    input[ 0 ][ "b" ] = Json::Value( "yep" );
    input[ 1 ][ "a" ] = Json::Value( 94 );
    input[ 1 ][ "b" ] = Json::Value( 4.3 );
    
    typedef std::array< s, 2 > array_t;

    EXPECT_THROW
        ( iscool::json::collection_cast< array_t >( input, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< array_t >
          ( Json::objectValue, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< array_t >
          ( Json::realValue, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< array_t >
          ( Json::intValue, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< array_t >
          ( Json::booleanValue, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< array_t >
          ( Json::nullValue, custom_cast ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::json::collection_cast< array_t >
          ( Json::uintValue, custom_cast ),
          iscool::json::bad_cast );
}

TEST( iscool_json_collection_cast, array_fail_size )
{
    struct s
    {
        int a;
        std::string b;
    };

    auto custom_cast
        ( []( const Json::Value& entry ) -> s
          {
              s result;
              result.a = iscool::json::cast< int >( entry[ "a" ] );
              result.b = iscool::json::cast< std::string >( entry[ "b" ] );
              return result;
          } );

    Json::Value input;
    input[ 0 ][ "a" ] = Json::Value( 1 );
    input[ 0 ][ "b" ] = Json::Value( "yep" );
    input[ 1 ][ "a" ] = Json::Value( 94 );
    input[ 1 ][ "b" ] = Json::Value( "great" );
    input[ 2 ][ "a" ] = Json::Value( 4 );
    input[ 2 ][ "b" ] = Json::Value( "nope" );
    
    typedef std::array< s, 2 > array_t;

    EXPECT_THROW
        ( iscool::json::collection_cast< array_t >( input, custom_cast ),
          iscool::json::bad_cast );
}

TEST( iscool_json_collection_cast, array_default_cast )
{
    Json::Value input;
    input[ 0 ] = Json::Value( "YEP" );
    input[ 1 ] = Json::Value( "GREAT" );
    
    const std::array< std::string, 2 > result
        ( iscool::json::collection_cast< std::array< std::string, 2 > >
          ( input ) );
    
    EXPECT_EQ( "YEP", result[ 0 ] );
    EXPECT_EQ( "GREAT", result[ 1 ] );
}
