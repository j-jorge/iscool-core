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
#include "iscool/preferences/property_deserializer.h"

#include "iscool/test/debug_crash.h"

#include <algorithm>
#include <unistd.h>

#include "gtest/gtest.h"

TEST( iscool_preferences_property_deserializer_test, values )
{
    std::unordered_map< std::string, std::string > properties;
    properties[ "int" ] = "24";
    properties[ "string" ] = "s";
    properties[ "bool" ] = "1";
    properties[ "float" ] = "2.6";
    properties[ "bool_unused" ] = "0";

    iscool::preferences::property_deserializer deserializer;
    deserializer.add_int_property( "int" );
    deserializer.add_string_property( "string" );
    deserializer.add_bool_property( "bool" );
    deserializer.add_float_property( "float" );

    EXPECT_DEBUG_CRASH( deserializer.add_int_property( "int" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_int_property( "string" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_int_property( "bool" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_int_property( "float" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_string_property( "int" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_string_property( "string" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_string_property( "bool" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_string_property( "float" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_bool_property( "int" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_bool_property( "string" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_bool_property( "bool" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_bool_property( "float" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_float_property( "int" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_float_property( "string" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_float_property( "bool" ) );
    EXPECT_DEBUG_CRASH( deserializer.add_float_property( "float" ) );
    
    iscool::preferences::property_map map;
    deserializer( map, properties );
    
    EXPECT_TRUE( map.has< int >( "int" ) );
    EXPECT_EQ( 24, *map.get< int >( "int" ) );
    
    EXPECT_TRUE( map.has< std::string >( "string" ) );
    EXPECT_EQ( "s", *map.get< std::string >( "string" ) );

    EXPECT_TRUE( map.has< bool >( "bool" ) );
    EXPECT_EQ( true, *map.get< bool >( "bool" ) );

    EXPECT_TRUE( map.has< float >( "float" ) );
    EXPECT_FLOAT_EQ( 2.6, *map.get< float >( "float" ) );

    EXPECT_FALSE( map.has< bool >( "bool_unused" ) );
    EXPECT_FALSE( map.has< int >( "bool_unused" ) );
    EXPECT_FALSE( map.has< std::string >( "bool_unused" ) );
}

TEST( iscool_preferences_property_deserializer_test, bad_int )
{
    std::unordered_map< std::string, std::string > properties;
    properties[ "int" ] = "iste";

    iscool::preferences::property_deserializer deserializer;
    deserializer.add_int_property( "int" );

    iscool::preferences::property_map map;
    deserializer( map, properties );
    
    EXPECT_FALSE( map.has< int >( "int" ) );
}

TEST( iscool_preferences_property_deserializer_test, bad_bool )
{
    std::unordered_map< std::string, std::string > properties;
    properties[ "bool" ] = "iste";

    iscool::preferences::property_deserializer deserializer;
    deserializer.add_bool_property( "bool" );

    iscool::preferences::property_map map;
    deserializer( map, properties );
    
    EXPECT_FALSE( map.has< bool >( "bool" ) );
}

TEST( iscool_preferences_property_deserializer_test, bad_float )
{
    std::unordered_map< std::string, std::string > properties;
    properties[ "float" ] = "9..2";

    iscool::preferences::property_deserializer deserializer;
    deserializer.add_float_property( "float" );

    iscool::preferences::property_map map;
    deserializer( map, properties );
    
    EXPECT_FALSE( map.has< float >( "float" ) );
}

TEST( iscool_preferences_property_deserializer_test, remove )
{
    iscool::preferences::property_deserializer deserializer;
    deserializer.add_int_property( "int" );
    deserializer.add_int_property( "int2" );
    deserializer.add_string_property( "string" );
    deserializer.add_string_property( "string2" );
    deserializer.add_bool_property( "bool" );
    deserializer.add_bool_property( "bool2" );
    deserializer.add_float_property( "float" );
    deserializer.add_float_property( "float2" );

    {
        const std::vector< std::string > keys( deserializer.get_all_keys() );

        const auto bit( keys.begin() );
        const auto eit( keys.end() );
    
        EXPECT_NE( eit, std::find( bit, eit, "int" ) );
        EXPECT_NE( eit, std::find( bit, eit, "int2" ) );
        EXPECT_NE( eit, std::find( bit, eit, "string" ) );
        EXPECT_NE( eit, std::find( bit, eit, "string2" ) );
        EXPECT_NE( eit, std::find( bit, eit, "bool" ) );
        EXPECT_NE( eit, std::find( bit, eit, "bool2" ) );
        EXPECT_NE( eit, std::find( bit, eit, "float" ) );
        EXPECT_NE( eit, std::find( bit, eit, "float2" ) );
    }

    deserializer.remove_int_property( "int2" );
    deserializer.remove_string_property( "string2" );
    deserializer.remove_bool_property( "bool2" );
    deserializer.remove_float_property( "float2" );

    {
        const std::vector< std::string > keys( deserializer.get_all_keys() );

        const auto bit( keys.begin() );
        const auto eit( keys.end() );
    
        EXPECT_NE( eit, std::find( bit, eit, "int" ) );
        EXPECT_EQ( eit, std::find( bit, eit, "int2" ) );
        EXPECT_NE( eit, std::find( bit, eit, "string" ) );
        EXPECT_EQ( eit, std::find( bit, eit, "string2" ) );
        EXPECT_NE( eit, std::find( bit, eit, "bool" ) );
        EXPECT_EQ( eit, std::find( bit, eit, "bool2" ) );
        EXPECT_NE( eit, std::find( bit, eit, "float" ) );
        EXPECT_EQ( eit, std::find( bit, eit, "float2" ) );
    }
}

TEST( iscool_preferences_property_deserializer_test, get_all_keys )
{
    iscool::preferences::property_deserializer deserializer;
    deserializer.add_int_property( "int" );
    deserializer.add_int_property( "int2" );
    deserializer.add_string_property( "string" );
    deserializer.add_bool_property( "bool" );
    deserializer.add_float_property( "float" );

    const std::vector< std::string > keys( deserializer.get_all_keys() );

    const auto bit( keys.begin() );
    const auto eit( keys.end() );
    
    EXPECT_NE( eit, std::find( bit, eit, "int" ) );
    EXPECT_NE( eit, std::find( bit, eit, "int2" ) );
    EXPECT_NE( eit, std::find( bit, eit, "string" ) );
    EXPECT_NE( eit, std::find( bit, eit, "bool" ) );
    EXPECT_NE( eit, std::find( bit, eit, "float" ) );
}

TEST( iscool_preferences_property_deserializer_test, merge )
{
    iscool::preferences::property_deserializer deserializer_1;
    deserializer_1.add_int_property( "int" );
    deserializer_1.add_string_property( "string" );
    deserializer_1.add_bool_property( "bool" );
    deserializer_1.add_float_property( "float" );

    iscool::preferences::property_deserializer deserializer_2;
    deserializer_2.add_int_property( "int2" );
    deserializer_2.add_string_property( "string2" );
    deserializer_2.add_bool_property( "bool2" );
    deserializer_2.add_float_property( "float2" );

    deserializer_1.merge( deserializer_2 );

    EXPECT_DEBUG_CRASH( deserializer_1.merge( deserializer_2 ) );
    
    std::unordered_map< std::string, std::string > properties;
    properties[ "int" ] = "24";
    properties[ "int2" ] = "42";
    properties[ "string" ] = "s";
    properties[ "string2" ] = "S";
    properties[ "bool" ] = "1";
    properties[ "bool2" ] = "0";
    properties[ "float" ] = "10.5";
    properties[ "float2" ] = "-0.9";

    iscool::preferences::property_map map;
    deserializer_1( map, properties );
    
    EXPECT_TRUE( map.has< int >( "int" ) );
    EXPECT_EQ( 24, *map.get< int >( "int" ) );
    
    EXPECT_TRUE( map.has< int >( "int2" ) );
    EXPECT_EQ( 42, *map.get< int >( "int2" ) );

    EXPECT_TRUE( map.has< std::string >( "string" ) );
    EXPECT_EQ( "s", *map.get< std::string >( "string" ) );

    EXPECT_TRUE( map.has< std::string >( "string2" ) );
    EXPECT_EQ( "S", *map.get< std::string >( "string2" ) );

    EXPECT_TRUE( map.has< bool >( "bool" ) );
    EXPECT_TRUE( *map.get< bool >( "bool" ) );

    EXPECT_TRUE( map.has< bool >( "bool2" ) );
    EXPECT_FALSE( *map.get< bool >( "bool2" ) );

    EXPECT_TRUE( map.has< float >( "float" ) );
    EXPECT_FLOAT_EQ( 10.5, *map.get< float >( "float" ) );

    EXPECT_TRUE( map.has< float >( "float2" ) );
    EXPECT_FLOAT_EQ( -0.9, *map.get< float >( "float2" ) );

    iscool::preferences::property_deserializer deserializer_3;
    deserializer_3.add_int_property( "string" );
    deserializer_3.add_string_property( "bool" );
    deserializer_3.add_bool_property( "int" );
    deserializer_3.add_bool_property( "float" );
    
    EXPECT_DEBUG_CRASH( deserializer_1.merge( deserializer_3 ) );
}

TEST( iscool_preferences_property_deserializer_test, copy )
{
    std::unordered_map< std::string, std::string > properties;
    properties[ "int" ] = "24";
    properties[ "string" ] = "s";
    properties[ "bool" ] = "1";
    properties[ "float" ] = "8.7";

    iscool::preferences::property_deserializer deserializer;
    deserializer.add_int_property( "int" );
    deserializer.add_string_property( "string" );
    deserializer.add_bool_property( "bool" );
    deserializer.add_float_property( "float" );

    const iscool::preferences::property_deserializer copy( deserializer );

    iscool::preferences::property_map map;
    copy( map, properties );
    
    EXPECT_TRUE( map.has< int >( "int" ) );
    EXPECT_EQ( 24, *map.get< int >( "int" ) );
    
    EXPECT_TRUE( map.has< std::string >( "string" ) );
    EXPECT_EQ( "s", *map.get< std::string >( "string" ) );

    EXPECT_TRUE( map.has< bool >( "bool" ) );
    EXPECT_EQ( true, *map.get< bool >( "bool" ) );

    EXPECT_TRUE( map.has< float >( "float" ) );
    EXPECT_FLOAT_EQ( 8.7, *map.get< float >( "float" ) );

}

