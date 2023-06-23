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
#ifndef ISCOOL_AUDIO_MIXER_H
#define ISCOOL_AUDIO_MIXER_H

#include "iscool/audio/track_id.h"

#include "iscool/resources/resolver.h"

#include <functional>
#include <unordered_map>
#include <vector>

namespace iscool
{
  namespace audio
  {
    enum class loop_mode;
    class platform_mixer;

    class mixer
    {
    public:
      mixer(const iscool::resources::resolver& resources,
            std::size_t min_frames_between_effects,
            platform_mixer& implementation);

      mixer(const mixer&) = delete;
      mixer& operator=(const mixer&) = delete;

      void tick();

      void set_effects_muted(bool muted);
      bool get_effects_muted() const;

      void set_music_muted(bool muted);
      bool get_music_muted() const;

      void play_music(const std::string& name, loop_mode loop);

      void preload_effect(const std::string& name);
      track_id play_effect(const std::string& name, loop_mode loop);
      void stop_effect(track_id id);

    private:
      bool should_skip_effect(const std::string& name) const;

    private:
      const iscool::resources::resolver _resources;
      const std::size_t _min_frames_between_effects;
      platform_mixer& _impl;

      std::vector<std::function<void()>> _commands;

      std::size_t _effects_muting;
      std::size_t _music_muting;
      std::size_t _date;

      std::string _current_music;

      std::unordered_map<std::string, std::size_t> _last_play_date;

      std::unordered_map<track_id, track_id> _id_to_impl_id;
      track_id _next_id;
    };
  }
}

#endif
