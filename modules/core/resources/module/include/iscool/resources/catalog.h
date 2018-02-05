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
#ifndef ISCOOL_RESOURCES_CATALOG_H
#define ISCOOL_RESOURCES_CATALOG_H

#include <vector>
#include <string>

namespace iscool
{
    namespace resources
    {
        class catalog
        {
        public:
            catalog();
            catalog
            ( const std::vector< std::string >& textures,
              const std::vector< std::string >& particles,
              const std::vector< std::string >& sounds,
              const std::vector< std::string >& styles );
              
            const std::vector< std::string >& get_textures() const;
            const std::vector< std::string >& get_particles() const;
            const std::vector< std::string >& get_sounds() const;
            const std::vector< std::string >& get_styles() const;
            const std::vector< std::string >& get_skeletons() const;
            const std::vector< std::string >& get_sprite_sheets() const;

            void insert( const catalog& that );
            
        private:
            void add_sprite_sheet_from_texture( const std::string& filename );
            void add_skeleton_from_texture( const std::string& filename );
            
        private:
            std::vector< std::string > _textures;
            std::vector< std::string > _skeletons;
            std::vector< std::string > _particles;
            std::vector< std::string > _sprite_sheets;
            std::vector< std::string > _sounds;
            std::vector< std::string > _styles;
        };
    }
}
            
#endif
