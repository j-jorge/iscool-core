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
#include <iscool/audio/loop_mode.hpp>
#include <iscool/audio/mixer.hpp>

#include <iscool/files/setup.hpp>

#include <iscool/audio/test/platform_mixer_mockup.hpp>
#include <iscool/files/test/file_system_delegates_mockup.hpp>

#include <gtest/gtest.h>

class iscool_audio_mixer_test : public ::testing::Test
{
public:
  iscool_audio_mixer_test();
  ~iscool_audio_mixer_test();

protected:
  static const std::string _resources_path;
  static const std::string _resources_extension;

  iscool::files::test::file_system_delegates_mockup _delegates;

  iscool::audio::tests::platform_mixer_mockup _implementation;
  iscool::audio::mixer _mixer;
};

const std::string iscool_audio_mixer_test::_resources_path("test");
const std::string iscool_audio_mixer_test::_resources_extension(".ext");

iscool_audio_mixer_test::iscool_audio_mixer_test()
  : _mixer(iscool::resources::resolver(_resources_path, _resources_extension),
           3, _implementation)
{
  _delegates.file_exists_impl = [](const std::string& path) -> bool
  {
    return path != _resources_path + "does-not-exist" + _resources_extension;
  };

  iscool::files::initialize(_delegates);
}

iscool_audio_mixer_test::~iscool_audio_mixer_test()
{
  iscool::files::finalize();
}

TEST_F(iscool_audio_mixer_test, mute_effects)
{
  EXPECT_FALSE(_mixer.get_effects_muted());

  _mixer.set_effects_muted(true);
  EXPECT_TRUE(_mixer.get_effects_muted());

  EXPECT_FALSE(_implementation.effects_muted);
  _mixer.tick();
  EXPECT_TRUE(_implementation.effects_muted);

  _mixer.set_effects_muted(false);
  EXPECT_FALSE(_mixer.get_effects_muted());

  EXPECT_TRUE(_implementation.effects_muted);
  _mixer.tick();
  EXPECT_FALSE(_implementation.effects_muted);

  _mixer.set_effects_muted(true);
  EXPECT_TRUE(_mixer.get_effects_muted());

  EXPECT_FALSE(_implementation.effects_muted);
  _mixer.tick();
  EXPECT_TRUE(_implementation.effects_muted);

  _mixer.set_effects_muted(true);
  EXPECT_TRUE(_mixer.get_effects_muted());

  EXPECT_TRUE(_implementation.effects_muted);
  _mixer.tick();
  EXPECT_TRUE(_implementation.effects_muted);

  _mixer.set_effects_muted(false);
  EXPECT_TRUE(_mixer.get_effects_muted());

  EXPECT_TRUE(_implementation.effects_muted);
  _mixer.tick();
  EXPECT_TRUE(_implementation.effects_muted);

  _mixer.set_effects_muted(false);
  EXPECT_FALSE(_mixer.get_effects_muted());

  EXPECT_TRUE(_implementation.effects_muted);
  _mixer.tick();
  EXPECT_FALSE(_implementation.effects_muted);
}

TEST_F(iscool_audio_mixer_test, mute_music)
{
  EXPECT_FALSE(_mixer.get_music_muted());

  _mixer.set_music_muted(true);
  EXPECT_TRUE(_mixer.get_music_muted());

  EXPECT_FALSE(_implementation.music_muted);
  _mixer.tick();
  EXPECT_TRUE(_implementation.music_muted);

  _mixer.set_music_muted(false);
  EXPECT_FALSE(_mixer.get_music_muted());

  EXPECT_TRUE(_implementation.music_muted);
  _mixer.tick();
  EXPECT_FALSE(_implementation.music_muted);

  _mixer.set_music_muted(true);
  EXPECT_TRUE(_mixer.get_music_muted());

  EXPECT_FALSE(_implementation.music_muted);
  _mixer.tick();
  EXPECT_TRUE(_implementation.music_muted);

  _mixer.set_music_muted(true);
  EXPECT_TRUE(_mixer.get_music_muted());

  EXPECT_TRUE(_implementation.music_muted);
  _mixer.tick();
  EXPECT_TRUE(_implementation.music_muted);

  _mixer.set_music_muted(false);
  EXPECT_TRUE(_mixer.get_music_muted());

  EXPECT_TRUE(_implementation.music_muted);
  _mixer.tick();
  EXPECT_TRUE(_implementation.music_muted);

  _mixer.set_music_muted(false);
  EXPECT_FALSE(_mixer.get_music_muted());

  EXPECT_TRUE(_implementation.music_muted);
  _mixer.tick();
  EXPECT_FALSE(_implementation.music_muted);
}

TEST_F(iscool_audio_mixer_test, play_music)
{
  EXPECT_FALSE(_implementation.music_stopped);

  _mixer.play_music("a", iscool::audio::loop_mode::once);
  _mixer.tick();

  EXPECT_TRUE(_implementation.music_stopped);
  EXPECT_EQ(_resources_path + "a" + _resources_extension,
            _implementation.last_music);
  EXPECT_EQ(iscool::audio::loop_mode::once, _implementation.music_loop);

  _implementation.music_stopped = false;
  _mixer.play_music("b", iscool::audio::loop_mode::once);
  _mixer.tick();

  EXPECT_TRUE(_implementation.music_stopped);
  EXPECT_EQ(_resources_path + "b" + _resources_extension,
            _implementation.last_music);
  EXPECT_EQ(iscool::audio::loop_mode::once, _implementation.music_loop);

  _implementation.music_stopped = false;
  _implementation.last_music.clear();

  _mixer.play_music("b", iscool::audio::loop_mode::once);
  _mixer.tick();

  EXPECT_TRUE(_implementation.last_music.empty());
  EXPECT_EQ(iscool::audio::loop_mode::once, _implementation.music_loop);

  _mixer.play_music("b", iscool::audio::loop_mode::forever);
  _mixer.tick();

  EXPECT_FALSE(_implementation.music_stopped);
  EXPECT_TRUE(_implementation.last_music.empty());
  EXPECT_EQ(iscool::audio::loop_mode::once, _implementation.music_loop);

  _mixer.play_music("c", iscool::audio::loop_mode::forever);
  _mixer.tick();

  EXPECT_TRUE(_implementation.music_stopped);
  EXPECT_EQ(_resources_path + "c" + _resources_extension,
            _implementation.last_music);
  EXPECT_EQ(iscool::audio::loop_mode::forever, _implementation.music_loop);

  _implementation.music_stopped = false;
  _implementation.last_music.clear();
  _mixer.tick();

  EXPECT_FALSE(_implementation.music_stopped);
  EXPECT_TRUE(_implementation.last_music.empty());
}

TEST_F(iscool_audio_mixer_test, play_music_non_existent_file)
{
  _mixer.play_music("does-not-exist", iscool::audio::loop_mode::once);
  _mixer.tick();
  EXPECT_TRUE(_implementation.last_music.empty());
}

TEST_F(iscool_audio_mixer_test, preload_effect)
{
  _mixer.preload_effect("a");
  EXPECT_TRUE(_implementation.preloaded.empty());

  _mixer.preload_effect("c");
  EXPECT_TRUE(_implementation.preloaded.empty());

  _mixer.preload_effect("b");
  EXPECT_TRUE(_implementation.preloaded.empty());

  _mixer.tick();

  const auto end(_implementation.preloaded.end());

  EXPECT_NE(end, _implementation.preloaded.find(_resources_path + "a"
                                                + _resources_extension));
  EXPECT_NE(end, _implementation.preloaded.find(_resources_path + "b"
                                                + _resources_extension));
  EXPECT_NE(end, _implementation.preloaded.find(_resources_path + "c"
                                                + _resources_extension));

  _implementation.preloaded.clear();
  EXPECT_TRUE(_implementation.preloaded.empty());
}

TEST_F(iscool_audio_mixer_test, preload_effect_non_existent_file)
{
  _mixer.preload_effect("does-not-exist");
  _mixer.tick();
  EXPECT_TRUE(_implementation.preloaded.empty());
}

TEST_F(iscool_audio_mixer_test, play_effect)
{
  const iscool::audio::track_id a_id(
      _mixer.play_effect("a", iscool::audio::loop_mode::once));
  EXPECT_TRUE(_implementation.effects.empty());
  EXPECT_TRUE(_implementation.effect_loops.empty());

  const iscool::audio::track_id b_id(
      _mixer.play_effect("b", iscool::audio::loop_mode::forever));
  EXPECT_TRUE(_implementation.effects.empty());
  EXPECT_TRUE(_implementation.effect_loops.empty());

  _mixer.tick();

  EXPECT_EQ(2, _implementation.effects.size());
  EXPECT_EQ(2, _implementation.effect_loops.size());

  const auto find_track(
      [this](const std::string& name) -> iscool::audio::track_id
      {
        const std::string resource(_resources_path + name
                                   + _resources_extension);

        for (const auto& e : _implementation.effects)
          if (e.second == resource)
            return e.first;

        return iscool::audio::not_a_track_id;
      });

  {
    const iscool::audio::track_id track(find_track("a"));

    EXPECT_NE(iscool::audio::not_a_track_id, track);

    const auto it(_implementation.effect_loops.find(track));
    EXPECT_NE(_implementation.effect_loops.end(), it);

    EXPECT_EQ(iscool::audio::loop_mode::once, it->second);
  }

  {
    const iscool::audio::track_id track(find_track("b"));

    EXPECT_NE(iscool::audio::not_a_track_id, track);

    const auto it(_implementation.effect_loops.find(track));
    EXPECT_NE(_implementation.effect_loops.end(), it);

    EXPECT_EQ(iscool::audio::loop_mode::forever, it->second);
  }

  const auto old_effects(_implementation.effects);
  const auto old_effect_loops(_implementation.effect_loops);

  _mixer.stop_effect(a_id);

  EXPECT_EQ(old_effects, _implementation.effects);
  EXPECT_EQ(old_effect_loops, _implementation.effect_loops);

  _mixer.tick();

  EXPECT_EQ(1, _implementation.effects.size());
  EXPECT_EQ(1, _implementation.effect_loops.size());

  {
    const iscool::audio::track_id track(find_track("b"));

    EXPECT_NE(iscool::audio::not_a_track_id, track);

    const auto it(_implementation.effect_loops.find(track));
    EXPECT_NE(_implementation.effect_loops.end(), it);

    EXPECT_EQ(iscool::audio::loop_mode::forever, it->second);
  }

  _mixer.stop_effect(b_id);
  _mixer.tick();

  EXPECT_TRUE(_implementation.effects.empty());
  EXPECT_TRUE(_implementation.effect_loops.empty());

  _mixer.stop_effect(b_id);
  _mixer.stop_effect(iscool::audio::not_a_track_id);
  _mixer.tick();
}

TEST_F(iscool_audio_mixer_test, play_effect_non_existent_file)
{
  _mixer.play_effect("does-not-exist", iscool::audio::loop_mode::once);
  _mixer.tick();
  EXPECT_TRUE(_implementation.effects.empty());
  EXPECT_TRUE(_implementation.effect_loops.empty());
}

TEST_F(iscool_audio_mixer_test, play_effect_min_delay)
{
  _mixer.play_effect("a", iscool::audio::loop_mode::once);
  _mixer.play_effect("a", iscool::audio::loop_mode::forever);
  _mixer.tick();

  ASSERT_EQ(1, _implementation.effects.size());
  ASSERT_EQ(1, _implementation.effect_loops.size());

  const iscool::audio::track_id first_id(
      _implementation.effects.begin()->first);
  const iscool::audio::loop_mode first_loop(
      _implementation.effect_loops.begin()->second);

  EXPECT_EQ(iscool::audio::loop_mode::once, first_loop);

  _mixer.play_effect("a", iscool::audio::loop_mode::forever);
  _mixer.tick();

  ASSERT_EQ(1, _implementation.effects.size());
  ASSERT_EQ(1, _implementation.effect_loops.size());
  EXPECT_EQ(first_id, _implementation.effects.begin()->first);
  EXPECT_EQ(first_loop, _implementation.effect_loops.begin()->second);

  _mixer.tick();
  _mixer.tick();
  _mixer.tick();
  _mixer.tick();
  _mixer.tick();
  _mixer.tick();

  ASSERT_EQ(1, _implementation.effects.size());
  ASSERT_EQ(1, _implementation.effect_loops.size());
  EXPECT_EQ(first_id, _implementation.effects.begin()->first);
  EXPECT_EQ(first_loop, _implementation.effect_loops.begin()->second);

  _mixer.play_effect("a", iscool::audio::loop_mode::forever);
  _mixer.tick();

  ASSERT_EQ(2, _implementation.effects.size());
  ASSERT_EQ(2, _implementation.effect_loops.size());

  _implementation.effects.erase(first_id);
  _implementation.effect_loops.erase(first_id);

  ASSERT_EQ(1, _implementation.effects.size());
  ASSERT_EQ(1, _implementation.effect_loops.size());
  EXPECT_NE(first_id, _implementation.effects.begin()->first);
  EXPECT_EQ(iscool::audio::loop_mode::forever,
            _implementation.effect_loops.begin()->second);
}
