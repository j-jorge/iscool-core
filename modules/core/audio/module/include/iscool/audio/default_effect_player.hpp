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
#ifndef ISCOOL_AUDIO_DEFAULT_EFFECT_PLAYER_H
#define ISCOOL_AUDIO_DEFAULT_EFFECT_PLAYER_H

#include <iscool/audio/track_id.hpp>

#include <string>

namespace iscool
{
  namespace audio
  {
    enum class loop_mode;

    track_id play_effect(const std::string& name, loop_mode loop);
    void stop_effect(track_id id);
  }
}

#endif
