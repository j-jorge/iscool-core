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
#include <iscool/audio/test/platform_mixer_mockup.hpp>

void iscool::audio::tests::platform_mixer_mockup::pause()
{
  paused = true;
}

void iscool::audio::tests::platform_mixer_mockup::resume()
{
  resumed = true;
}

void iscool::audio::tests::platform_mixer_mockup::set_effects_muted(bool muted)
{
  effects_muted = muted;
}

void iscool::audio::tests::platform_mixer_mockup::set_music_muted(bool muted)
{
  music_muted = muted;
}

void iscool::audio::tests::platform_mixer_mockup::play_music(
    const std::string& name, loop_mode loop)
{
  last_music = name;
  music_loop = loop;
}

void iscool::audio::tests::platform_mixer_mockup::stop_music()
{
  music_stopped = true;
}

void iscool::audio::tests::platform_mixer_mockup::preload_effect(
    const std::string& name)
{
  preloaded.insert(name);
}

iscool::audio::track_id
iscool::audio::tests::platform_mixer_mockup::play_effect(
    const std::string& name, loop_mode loop)
{
  const iscool::audio::track_id result(_next_effect_id);
  _next_effect_id += 7;

  effects[result] = name;
  effect_loops[result] = loop;

  return result;
}

void iscool::audio::tests::platform_mixer_mockup::stop_effect(track_id id)
{
  effects.erase(id);
  effect_loops.erase(id);
}
