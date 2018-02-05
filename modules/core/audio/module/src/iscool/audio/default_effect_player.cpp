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

#include "iscool/audio/detail/default_mixer.h"

iscool::audio::track_id iscool::audio::play_effect
( const std::string& name, loop_mode loop )
{
    return detail::get_default_mixer().play_effect( name, loop );
}

void iscool::audio::stop_effect( track_id id )
{
    detail::get_default_mixer().stop_effect( id );
}
