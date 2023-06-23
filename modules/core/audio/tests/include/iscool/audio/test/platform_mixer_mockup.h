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
#ifndef ISCOOL_AUDIO_TEST_PLATFORM_MIXER_MOCKUP_H
#define ISCOOL_AUDIO_TEST_PLATFORM_MIXER_MOCKUP_H

#include "iscool/audio/platform_mixer.h"

#include <unordered_map>
#include <unordered_set>

namespace iscool
{
  namespace audio
  {
    namespace tests
    {
      class platform_mixer_mockup : public iscool::audio::platform_mixer
      {
      public:
        void set_effects_muted(bool muted) override;
        void set_music_muted(bool muted) override;

        void play_music(const std::string& name, loop_mode loop) override;
        void stop_music() override;

        void preload_effect(const std::string& name) override;
        track_id play_effect(const std::string& name, loop_mode loop) override;
        void stop_effect(track_id id) override;

      public:
        bool effects_muted = false;
        bool music_muted = false;

        bool music_stopped = false;
        std::string last_music;
        loop_mode music_loop;

        std::unordered_set<std::string> preloaded;

        std::unordered_map<track_id, std::string> effects;
        std::unordered_map<track_id, loop_mode> effect_loops;

      private:
        track_id _next_effect_id = 12;
      };
    }
  }
}

#endif
