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
#include <iscool/resources/catalog.hpp>

#include <iscool/collections/has_duplicates.hpp>
#include <iscool/files/file_exists.hpp>
#include <iscool/resources/detail/check_extension.hpp>

#include <cassert>

iscool::resources::catalog::catalog::catalog() = default;

iscool::resources::catalog::catalog(const std::vector<std::string>& textures,
                                    const std::vector<std::string>& particles,
                                    const std::vector<std::string>& sounds,
                                    const std::vector<std::string>& styles)
  : _textures(textures)
  , _particles(particles)
  , _sounds(sounds)
  , _styles(styles)
{
  assert(
      !iscool::collections::has_duplicates(textures.begin(), textures.end()));
  assert(!iscool::collections::has_duplicates(particles.begin(),
                                              particles.end()));
  assert(!iscool::collections::has_duplicates(sounds.begin(), sounds.end()));
  assert(!iscool::collections::has_duplicates(styles.begin(), styles.end()));

  for (const std::string& t : textures)
    {
      add_sprite_sheet_from_texture(t);
      add_skeleton_from_texture(t);
    }

  assert(!iscool::collections::has_duplicates(_skeletons.begin(),
                                              _skeletons.end()));
  assert(!iscool::collections::has_duplicates(_sprite_sheets.begin(),
                                              _sprite_sheets.end()));
}

const std::vector<std::string>&
iscool::resources::catalog::get_textures() const
{
  return _textures;
}

const std::vector<std::string>&
iscool::resources::catalog::get_particles() const
{
  return _particles;
}

const std::vector<std::string>& iscool::resources::catalog::get_sounds() const
{
  return _sounds;
}

const std::vector<std::string>& iscool::resources::catalog::get_styles() const
{
  return _styles;
}

const std::vector<std::string>&
iscool::resources::catalog::get_skeletons() const
{
  return _skeletons;
}

const std::vector<std::string>&
iscool::resources::catalog::get_sprite_sheets() const
{
  return _sprite_sheets;
}

void iscool::resources::catalog::insert(const catalog& that)
{
  _textures.insert(_textures.end(), that._textures.begin(),
                   that._textures.end());
  assert(!iscool::collections::has_duplicates(_textures.begin(),
                                              _textures.end()));

  _skeletons.insert(_skeletons.end(), that._skeletons.begin(),
                    that._skeletons.end());
  assert(!iscool::collections::has_duplicates(_skeletons.begin(),
                                              _skeletons.end()));

  _particles.insert(_particles.end(), that._particles.begin(),
                    that._particles.end());
  assert(!iscool::collections::has_duplicates(_particles.begin(),
                                              _particles.end()));

  _sprite_sheets.insert(_sprite_sheets.end(), that._sprite_sheets.begin(),
                        that._sprite_sheets.end());
  assert(!iscool::collections::has_duplicates(_sprite_sheets.begin(),
                                              _sprite_sheets.end()));

  _sounds.insert(_sounds.end(), that._sounds.begin(), that._sounds.end());
  assert(!iscool::collections::has_duplicates(_sounds.begin(), _sounds.end()));

  _styles.insert(_styles.end(), that._styles.begin(), that._styles.end());
  assert(!iscool::collections::has_duplicates(_styles.begin(), _styles.end()));
}

void iscool::resources::catalog::add_sprite_sheet_from_texture(
    const std::string& filename)
{
  std::string::size_type i(detail::check_extension(".png", filename));

  if (i == std::string::npos)
    {
      i = detail::check_extension(".jpg", filename);
      if (i == std::string::npos)
        return;
    }

  const std::string sprite_sheet(filename.substr(0, i) + ".plist");

  if (iscool::files::file_exists(sprite_sheet))
    _sprite_sheets.push_back(sprite_sheet);
}

void iscool::resources::catalog::add_skeleton_from_texture(
    const std::string& filename)
{
  const std::string::size_type i(detail::check_extension(".png", filename));

  if (i == std::string::npos)
    return;

  const std::string prefix(filename.substr(0, i));

  if (iscool::files::file_exists(prefix + ".json")
      && iscool::files::file_exists(prefix + ".atlas"))
    _skeletons.push_back(prefix);
}
