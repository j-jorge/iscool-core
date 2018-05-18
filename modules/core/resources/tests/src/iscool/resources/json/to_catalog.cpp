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
#include "iscool/resources/json/to_catalog.h"

#include "iscool/files/setup.h"
#include "iscool/json/bad_cast.h"
#include "iscool/json/parse_string.h"

#include "iscool/files/test/file_system_delegates_mockup.h"
#include "iscool/test/equal_collections.h"

#include "gtest/gtest.h"

TEST( iscool_resources_catalog_json, to_catalog )
{
    static const char* json =
        "{"
        "  \"textures\":"
        "    [ \"texture1.jpg\", \"texture.png\", \"texture3.png\" ],"
        "  \"particles\": [ \"particles_1\", \"particles_2\" ],"
        "  \"sounds\": [ \"sound_1\", \"sound_2\", \"sound_9\" ],"
        "  \"styles\": [ \"style.json\", \"style-b.json\" ]"
        "}";
    
    iscool::files::test::file_system_delegates_mockup delegates;
    
    delegates.file_exists_impl =
        []( const std::string& s ) -> bool
    {
        return
            ( s == "texture.json" ) || ( s == "texture.atlas" )
            || ( s == "texture1.plist" ) || ( s == "texture3.plist" );
    };
    
    iscool::files::initialize( delegates );

    const iscool::resources::catalog catalog
        ( iscool::resources::json::to_catalog
          ( iscool::json::parse_string( json ) ) );

    const std::vector< std::string > textures
        {
            "texture.png",
            "texture1.jpg",
            "texture3.png"
        };
    iscool::test::assert_equal_collections( textures, catalog.get_textures() );

    const std::vector< std::string > particles
        {
            "particles_1",
            "particles_2"
        };
    iscool::test::assert_equal_collections
        ( particles, catalog.get_particles() );

    const std::vector< std::string > sounds
        {
            "sound_1",
            "sound_2",
            "sound_9"
        };
    iscool::test::assert_equal_collections( sounds, catalog.get_sounds() );
    
    const std::vector< std::string > styles
        {
            "style.json",
            "style-b.json"
        };
    iscool::test::assert_equal_collections( styles, catalog.get_styles() );

    const std::vector< std::string > skeletons
        {
            "texture"
        };
    
    iscool::test::assert_equal_collections
        ( skeletons, catalog.get_skeletons() );

    const std::vector< std::string > sprite_sheets
        {
            "texture1.plist",
            "texture3.plist"
        };
    
    iscool::test::assert_equal_collections
        ( sprite_sheets, catalog.get_sprite_sheets() );

    iscool::files::finalize();
}

TEST( iscool_resources_catalog_json, to_catalog_empty )
{
    static const char* json =
        "{"
        "  \"textures\": []"
        "}";
    
    iscool::files::initialize
        ( iscool::files::test::default_file_system_delegates_mockup() );

    const iscool::resources::catalog catalog
        ( iscool::resources::json::to_catalog
          ( iscool::json::parse_string( json ) ) );

    EXPECT_TRUE( catalog.get_textures().empty() );
    EXPECT_TRUE( catalog.get_particles().empty() );
    EXPECT_TRUE( catalog.get_sounds().empty() );
    EXPECT_TRUE( catalog.get_styles().empty() );
    EXPECT_TRUE( catalog.get_skeletons().empty() );
    EXPECT_TRUE( catalog.get_sprite_sheets().empty() );

    iscool::files::finalize();
}

TEST( iscool_resources_catalog_json, to_catalog_fail )
{
    static const char* json =
        "{"
        "  \"textures\": {},"
        "  \"particles\": [ \"particles_1\", \"particles_2\" ],"
        "  \"sounds\": [ \"sound_1\", \"sound_2\", \"sound_9\" ],"
        "  \"styles\": [ \"style.json\", \"style-b.json\" ]"
        "}";
    
    iscool::files::initialize
        ( iscool::files::test::default_file_system_delegates_mockup() );

    EXPECT_THROW
        ( iscool::resources::json::to_catalog
          ( iscool::json::parse_string( json ) ),
          iscool::json::bad_cast );

    iscool::files::finalize();
}

TEST( iscool_resources_catalog_json, to_catalog_fail_general )
{
    iscool::files::initialize
        ( iscool::files::test::default_file_system_delegates_mockup() );

    EXPECT_THROW
        ( iscool::resources::json::to_catalog( Json::Value() ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::resources::json::to_catalog( Json::intValue ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::resources::json::to_catalog( Json::uintValue ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::resources::json::to_catalog( Json::arrayValue ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::resources::json::to_catalog( Json::stringValue ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::resources::json::to_catalog( Json::realValue ),
          iscool::json::bad_cast );
    EXPECT_THROW
        ( iscool::resources::json::to_catalog( Json::booleanValue ),
          iscool::json::bad_cast );

    iscool::files::finalize();
}
