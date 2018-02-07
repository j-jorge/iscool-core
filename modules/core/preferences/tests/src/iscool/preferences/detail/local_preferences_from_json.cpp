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
#include "iscool/preferences/detail/local_preferences_from_json.h"

#include "iscool/preferences/property_map.impl.h"

#include "json/value.h"

#include <functional>
#include <unistd.h>

#include "gtest/gtest.h"

TEST( iscool_preferences_local_preferences_from_json_test, values )
{
    Json::Value json;
    json[ "int" ] = 24;
    json[ "string" ] = "s";
    json[ "bool" ] = true;
    
    const iscool::preferences::property_map map
        ( iscool::preferences::detail::local_preferences_from_json( json ) );

    EXPECT_TRUE( map.has< int >( "int" ) );
    EXPECT_EQ( 24, *map.get< int >( "int" ) );
    
    EXPECT_TRUE( map.has< std::string >( "string" ) );
    EXPECT_EQ( "s", *map.get< std::string >( "string" ) );

    EXPECT_TRUE( map.has< bool >( "bool" ) );
    EXPECT_EQ( true, *map.get< bool >( "bool" ) );
}

TEST( iscool_preferences_local_preferences_from_json_test, non_object )
{
    Json::Value json( 53489 );
    
    const iscool::preferences::property_map map
        ( iscool::preferences::detail::local_preferences_from_json( json ) );

    EXPECT_TRUE( map.empty() );
}

struct key_visitor
{
    template< typename T >
    void operator()( const std::string& key, const T& )
    {
        if ( key == "array" )
            array_key = true;
        else if ( key == "double" )
            double_key = true;
        else if ( key == "object" )
            object_key = true;
        else if ( key == "int" )
            int_key = true;
    }

    bool int_key = false;
    bool array_key = false;
    bool double_key = false;
    bool object_key = false;
};

TEST( iscool_preferences_local_preferences_from_json_test, skip_fields )
{
    Json::Value json;
    json[ "int" ] = 24;

    json[ "array" ][ 0 ] = 18;
    json[ "object" ][ "member" ] = 18;
    json[ "double" ] = 1.8;
    
    const iscool::preferences::property_map map
        ( iscool::preferences::detail::local_preferences_from_json( json ) );

    key_visitor visitor;
    map.visit( std::ref( visitor ) );
    
    EXPECT_TRUE( visitor.int_key );
    EXPECT_FALSE( visitor.array_key );
    EXPECT_FALSE( visitor.object_key );
    EXPECT_FALSE( visitor.double_key );
}
