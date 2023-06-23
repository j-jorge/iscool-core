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
#include "iscool/resources/catalog.h"

#include "iscool/files/setup.h"

#include "iscool/files/test/file_system_delegates_mockup.h"
#include "iscool/test/equal_collections.h"

#include "gtest/gtest.h"

TEST(iscool_resources_catalog, texture)
{
  iscool::files::initialize(
      iscool::files::test::file_system_delegates_mockup());

  const std::vector<std::string> textures{ "texture_1", "texture_2" };

  const std::vector<std::string> particles{ "particles_1", "particles_2",
                                            "particles_3" };

  const std::vector<std::string> sounds{ "sounds_1", "sounds_3" };

  const std::vector<std::string> styles{ "styles_3" };

  const iscool::resources::catalog catalog(textures, particles, sounds,
                                           styles);

  iscool::test::assert_equal_collections(textures, catalog.get_textures());
  iscool::test::assert_equal_collections(particles, catalog.get_particles());
  iscool::test::assert_equal_collections(sounds, catalog.get_sounds());
  iscool::test::assert_equal_collections(styles, catalog.get_styles());

  iscool::files::finalize();
}

TEST(iscool_resources_catalog, skeleton)
{
  iscool::files::test::file_system_delegates_mockup delegates;

  delegates.file_exists_impl = [](const std::string& s) -> bool
  {
    return (s == "texture.json") || (s == "texture.atlas");
  };

  iscool::files::initialize(delegates);

  const std::vector<std::string> textures{ "texture1.png", "texture.png" };
  const std::vector<std::string> empty;
  const iscool::resources::catalog catalog(textures, empty, empty, empty);
  ;
  const std::vector<std::string> expected{ "texture" };

  iscool::test::assert_equal_collections(expected, catalog.get_skeletons());

  iscool::files::finalize();
}

TEST(iscool_resources_catalog, sprite_sheet)
{
  iscool::files::test::file_system_delegates_mockup delegates;

  delegates.file_exists_impl = [](const std::string& s) -> bool
  {
    return s == "texture.plist";
  };

  iscool::files::initialize(delegates);

  const std::vector<std::string> textures{ "texture1.png", "texture.png" };
  const std::vector<std::string> empty;
  const iscool::resources::catalog catalog(textures, empty, empty, empty);
  ;
  const std::vector<std::string> expected{ "texture.plist" };

  iscool::test::assert_equal_collections(expected,
                                         catalog.get_sprite_sheets());

  iscool::files::finalize();
}

TEST(iscool_resources_catalog, insert)
{
  iscool::files::test::file_system_delegates_mockup delegates;

  delegates.file_exists_impl = [](const std::string& s) -> bool
  {
    return (s == "a_skeleton.json") || (s == "a_skeleton.atlas")
           || (s == "a_sprite_sheet.plist") || (s == "b_skeleton.json")
           || (s == "b_skeleton.atlas") || (s == "b_sprite_sheet.plist");
  };

  iscool::files::initialize(delegates);

  const std::vector<std::string> textures_a{
    "a_texture.png", "a_sprite_sheet.png", "a_skeleton1.png", "a_skeleton.png"
  };

  const std::vector<std::string> particles_a{ "a_particles_1", "a_particles_2",
                                              "a_particles_3" };

  const std::vector<std::string> sounds_a{ "a_sounds_1", "a_sounds_3" };

  const std::vector<std::string> styles_a{ "a_styles_3" };

  iscool::resources::catalog catalog(textures_a, particles_a, sounds_a,
                                     styles_a);

  const std::vector<std::string> textures_b{
    "b_texture.png", "b_sprite_sheet.png", "b_skeleton1.png", "b_skeleton.png"
  };

  const std::vector<std::string> particles_b{ "b_particles_1", "b_particles_2",
                                              "b_particles_3" };

  const std::vector<std::string> sounds_b{ "b_sounds_1", "b_sounds_3" };

  const std::vector<std::string> styles_b{ "b_styles_3" };

  catalog.insert(
      iscool::resources::catalog(textures_b, particles_b, sounds_b, styles_b));

  const std::vector<std::string> expected_textures{
    "a_texture.png", "a_sprite_sheet.png", "a_skeleton1.png", "a_skeleton.png",
    "b_texture.png", "b_sprite_sheet.png", "b_skeleton1.png", "b_skeleton.png"
  };

  const std::vector<std::string> expected_particles{
    "a_particles_1", "a_particles_2", "a_particles_3",
    "b_particles_1", "b_particles_2", "b_particles_3"
  };

  const std::vector<std::string> expected_sounds{ "a_sounds_1", "a_sounds_3",
                                                  "b_sounds_1", "b_sounds_3" };

  const std::vector<std::string> expected_styles{ "a_styles_3", "b_styles_3" };

  const std::vector<std::string> expected_skeletons{ "a_skeleton",
                                                     "b_skeleton" };

  const std::vector<std::string> expected_sprite_sheets{
    "a_sprite_sheet.plist", "b_sprite_sheet.plist"
  };

  iscool::test::assert_equal_collections(expected_textures,
                                         catalog.get_textures());
  iscool::test::assert_equal_collections(expected_particles,
                                         catalog.get_particles());
  iscool::test::assert_equal_collections(expected_sounds,
                                         catalog.get_sounds());
  iscool::test::assert_equal_collections(expected_styles,
                                         catalog.get_styles());
  iscool::test::assert_equal_collections(expected_skeletons,
                                         catalog.get_skeletons());
  iscool::test::assert_equal_collections(expected_sprite_sheets,
                                         catalog.get_sprite_sheets());

  iscool::files::finalize();
}
