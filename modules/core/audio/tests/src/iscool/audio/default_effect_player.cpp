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
#include "iscool/audio/default_effect_player.h"
#include "iscool/audio/default_mixer.h"
#include "iscool/audio/loop_mode.h"
#include "iscool/audio/mixer.h"

#include "iscool/files/setup.h"

#include "iscool/audio/test/platform_mixer_mockup.h"
#include "iscool/files/test/empty_file_delegates.h"

#include <gtest/gtest.h>

class iscool_audio_default_effect_player_test:
    public ::testing::Test
{
public:
    iscool_audio_default_effect_player_test();
    ~iscool_audio_default_effect_player_test();
    
protected:
    static const std::string _resources_path;
    static const std::string _resources_extension;

    iscool::audio::tests::platform_mixer_mockup _implementation;
    iscool::audio::mixer _mixer;
};


const std::string
iscool_audio_default_effect_player_test::_resources_path( "test" );
const std::string
iscool_audio_default_effect_player_test::_resources_extension( ".ext" );

iscool_audio_default_effect_player_test::iscool_audio_default_effect_player_test
()
    : _mixer
      ( iscool::resources::resolver( _resources_path, _resources_extension ), 3,
        _implementation )
{
    iscool::files::file_system_delegates delegates
        ( iscool::files::test::create_empty_delegates() );

    delegates.file_exists =
        []( const std::string& path ) -> bool
        {
            return path !=
                _resources_path + "does-not-exist" + _resources_extension;
        };
    
    iscool::files::initialize( delegates );

    iscool::audio::set_default_mixer( _mixer );
}

iscool_audio_default_effect_player_test
::~iscool_audio_default_effect_player_test()
{
    iscool::audio::clear_default_mixer();
    iscool::files::finalize();
}

TEST_F( iscool_audio_default_effect_player_test, play_effect )
{
    const iscool::audio::track_id a_id
        ( iscool::audio::play_effect( "a", iscool::audio::loop_mode::once ) );
    EXPECT_TRUE( _implementation.effects.empty() );
    EXPECT_TRUE( _implementation.effect_loops.empty() );
    
    const iscool::audio::track_id b_id
        ( iscool::audio::play_effect
          ( "b", iscool::audio::loop_mode::forever ) );
    EXPECT_TRUE( _implementation.effects.empty() );
    EXPECT_TRUE( _implementation.effect_loops.empty() );
    
    _mixer.tick();

    EXPECT_EQ( 2, _implementation.effects.size() );
    EXPECT_EQ( 2, _implementation.effect_loops.size() );
    
    const auto find_track
        ( [ this ]( const std::string& name ) -> iscool::audio::track_id
          {
              const std::string resource
                  ( _resources_path + name + _resources_extension );
              
              for ( const auto& e : _implementation.effects )
                  if ( e.second == resource )
                      return e.first;

              return iscool::audio::not_a_track_id;
          } );

    {
        const iscool::audio::track_id track( find_track( "a" ) );
        
        EXPECT_NE( iscool::audio::not_a_track_id, track );

        const auto it( _implementation.effect_loops.find( track ) );
        EXPECT_NE( _implementation.effect_loops.end(), it );

        EXPECT_EQ( iscool::audio::loop_mode::once, it->second );
    }

    {
        const iscool::audio::track_id track( find_track( "b" ) );
        
        EXPECT_NE( iscool::audio::not_a_track_id, track );

        const auto it( _implementation.effect_loops.find( track ) );
        EXPECT_NE( _implementation.effect_loops.end(), it );

        EXPECT_EQ( iscool::audio::loop_mode::forever, it->second );
    }

    const auto old_effects( _implementation.effects );
    const auto old_effect_loops( _implementation.effect_loops );
    
    iscool::audio::stop_effect( a_id );

    EXPECT_EQ( old_effects, _implementation.effects );
    EXPECT_EQ( old_effect_loops, _implementation.effect_loops );

    _mixer.tick();
    
    EXPECT_EQ( 1, _implementation.effects.size() );
    EXPECT_EQ( 1, _implementation.effect_loops.size() );

    {
        const iscool::audio::track_id track( find_track( "b" ) );
        
        EXPECT_NE( iscool::audio::not_a_track_id, track );

        const auto it( _implementation.effect_loops.find( track ) );
        EXPECT_NE( _implementation.effect_loops.end(), it );

        EXPECT_EQ( iscool::audio::loop_mode::forever, it->second );
    }

    iscool::audio::stop_effect( b_id );
    _mixer.tick();
    
    EXPECT_TRUE( _implementation.effects.empty() );
    EXPECT_TRUE( _implementation.effect_loops.empty() );

    iscool::audio::stop_effect( b_id );
    iscool::audio::stop_effect( iscool::audio::not_a_track_id );
    _mixer.tick();
}

TEST_F( iscool_audio_default_effect_player_test, play_effect_non_existent_file )
{
    iscool::audio::play_effect
        ( "does-not-exist", iscool::audio::loop_mode::once );
    _mixer.tick();
    EXPECT_TRUE( _implementation.effects.empty() );
    EXPECT_TRUE( _implementation.effect_loops.empty() );
}

TEST_F( iscool_audio_default_effect_player_test, play_effect_min_delay )
{
    iscool::audio::play_effect( "a", iscool::audio::loop_mode::once );
    iscool::audio::play_effect( "a", iscool::audio::loop_mode::forever );
    _mixer.tick();

    ASSERT_EQ( 1, _implementation.effects.size() );
    ASSERT_EQ( 1, _implementation.effect_loops.size() );

    const iscool::audio::track_id first_id
        ( _implementation.effects.begin()->first );
    const iscool::audio::loop_mode first_loop
        ( _implementation.effect_loops.begin()->second );

    EXPECT_EQ( iscool::audio::loop_mode::once, first_loop );
    
    iscool::audio::play_effect( "a", iscool::audio::loop_mode::forever );
    _mixer.tick();

    ASSERT_EQ( 1, _implementation.effects.size() );
    ASSERT_EQ( 1, _implementation.effect_loops.size() );
    EXPECT_EQ( first_id, _implementation.effects.begin()->first );
    EXPECT_EQ( first_loop, _implementation.effect_loops.begin()->second );
    
    _mixer.tick();
    _mixer.tick();
    _mixer.tick();
    _mixer.tick();
    _mixer.tick();
    _mixer.tick();

    ASSERT_EQ( 1, _implementation.effects.size() );
    ASSERT_EQ( 1, _implementation.effect_loops.size() );
    EXPECT_EQ( first_id, _implementation.effects.begin()->first );
    EXPECT_EQ( first_loop, _implementation.effect_loops.begin()->second );
    
    iscool::audio::play_effect( "a", iscool::audio::loop_mode::forever );
    _mixer.tick();

    ASSERT_EQ( 2, _implementation.effects.size() );
    ASSERT_EQ( 2, _implementation.effect_loops.size() );

    _implementation.effects.erase( first_id );
    _implementation.effect_loops.erase( first_id );
    
    ASSERT_EQ( 1, _implementation.effects.size() );
    ASSERT_EQ( 1, _implementation.effect_loops.size() );
    EXPECT_NE( first_id, _implementation.effects.begin()->first );
    EXPECT_EQ
        ( iscool::audio::loop_mode::forever,
          _implementation.effect_loops.begin()->second );
}
