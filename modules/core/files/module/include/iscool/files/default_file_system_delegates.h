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
#ifndef ISCOOL_CORE_FILES_DEFAULT_FILE_SYSTEM_DELEGATES_H
#define ISCOOL_CORE_FILES_DEFAULT_FILE_SYSTEM_DELEGATES_H

#include "iscool/files/file_system_delegates.h"

#include <string>

namespace iscool
{
    namespace files
    {
        class default_file_system_delegates:
            public file_system_delegates
        {
        public:
            default_file_system_delegates
            ( const std::string& root, const std::string& writable_path );

            std::unique_ptr< std::istream > read_file
            ( const std::string& path ) const override;
            
            std::string get_writable_path() const override;
            bool file_exists( const std::string& path ) const override;
            std::string get_full_path( const std::string& path ) const override;

        private:
            const std::string _root;
            const std::string _writable_path;
        };
    }
}

#endif
