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
#ifndef ISCOOL_AUDIO_PLATFORM_MIXER_H
#define ISCOOL_AUDIO_PLATFORM_MIXER_H

#include "iscool/audio/track_id.h"

#include <string>

namespace iscool
{
  namespace audio
  {
    enum class loop_mode;

    class platform_mixer
    {
    public:
      virtual ~platform_mixer() = default;

      virtual void set_effects_muted(bool muted) = 0;
      virtual void set_music_muted(bool muted) = 0;

      virtual void play_music(const std::string& file_path,
                              loop_mode loop) = 0;
      virtual void stop_music() = 0;

      virtual void preload_effect(const std::string& file_path) = 0;
      virtual track_id play_effect(const std::string& file_path,
                                   loop_mode loop) = 0;
      virtual void stop_effect(track_id id) = 0;
    };
  }
}

#endif
