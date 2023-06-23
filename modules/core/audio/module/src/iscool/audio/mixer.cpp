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
#include <iscool/audio/mixer.hpp>

#include <iscool/audio/platform_mixer.hpp>
#include <iscool/files/file_exists.hpp>

#include <cassert>

iscool::audio::mixer::mixer(const iscool::resources::resolver& resources,
                            std::size_t min_frames_between_effects,
                            platform_mixer& implementation)
  : _resources(resources)
  , _min_frames_between_effects(min_frames_between_effects)
  , _impl(implementation)
  , _effects_muting(0)
  , _music_muting(0)
  , _date(0)
  , _next_id(0)
{}

void iscool::audio::mixer::tick()
{
  ++_date;

  std::vector<std::function<void()>> commands;
  commands.swap(_commands);

  for (const auto& command : commands)
    command();
}

void iscool::audio::mixer::set_effects_muted(bool muted)
{
  if (_effects_muting == 0)
    {
      assert(muted);
      ++_effects_muting;
      _commands.push_back(
          [this]() -> void
          {
            _impl.set_effects_muted(true);
          });
    }
  else
    {
      _effects_muting += muted ? 1 : -1;

      if (_effects_muting == 0)
        {
          assert(!muted);

          _commands.push_back(
              [this]() -> void
              {
                _impl.set_effects_muted(false);
              });
        }
    }
}

bool iscool::audio::mixer::get_effects_muted() const
{
  return _effects_muting != 0;
}

void iscool::audio::mixer::set_music_muted(bool muted)
{
  if (_music_muting == 0)
    {
      assert(muted);
      ++_music_muting;
      _commands.push_back(
          [this]() -> void
          {
            _impl.set_music_muted(true);
          });
    }
  else
    {
      _music_muting += muted ? 1 : -1;

      if (_music_muting == 0)
        {
          assert(!muted);

          _commands.push_back(
              [this]() -> void
              {
                _impl.set_music_muted(false);
              });
        }
    }
}

bool iscool::audio::mixer::get_music_muted() const
{
  return _music_muting != 0;
}

void iscool::audio::mixer::play_music(const std::string& name, loop_mode loop)
{
  _commands.push_back(
      [this, name, loop]() -> void
      {
        if (name == _current_music)
          return;

        _impl.stop_music();

        _current_music = name;

        const std::string path(_resources.get_file_path(name));

        if (iscool::files::file_exists(path))
          _impl.play_music(path, loop);
      });
}

void iscool::audio::mixer::preload_effect(const std::string& name)
{
  _commands.push_back(
      [this, name]() -> void
      {
        const std::string path(_resources.get_file_path(name));

        if (iscool::files::file_exists(path))
          _impl.preload_effect(path);
      });
}

iscool::audio::track_id
iscool::audio::mixer::play_effect(const std::string& name, loop_mode loop)
{
  const track_id result(_next_id);
  ++_next_id;

  _commands.push_back(
      [this, result, name, loop]() -> void
      {
        if (should_skip_effect(name))
          return;

        _last_play_date[name] = _date;

        const std::string path(_resources.get_file_path(name));
        track_id id;

        if (iscool::files::file_exists(path))
          id = _impl.play_effect(path, loop);
        else
          id = not_a_track_id;

        _id_to_impl_id[result] = id;
      });

  return result;
}

void iscool::audio::mixer::stop_effect(track_id id)
{
  _commands.push_back(
      [this, id]() -> void
      {
        const auto it(_id_to_impl_id.find(id));

        if (it == _id_to_impl_id.end())
          return;

        _impl.stop_effect(it->second);
        _id_to_impl_id.erase(it);
      });
}

bool iscool::audio::mixer::should_skip_effect(const std::string& name) const
{
  const auto it(_last_play_date.find(name));

  if (it == _last_play_date.end())
    return false;

  return _date - it->second < _min_frames_between_effects;
}
