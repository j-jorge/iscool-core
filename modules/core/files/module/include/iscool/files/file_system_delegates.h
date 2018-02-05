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
#ifndef ISCOOL_FILES_FILE_SYSTEM_DELEGATES_H
#define ISCOOL_FILES_FILE_SYSTEM_DELEGATES_H

#include <boost/function.hpp>
#include <memory>
#include <iostream>

namespace iscool
{
    namespace files
    {
        class file_system_delegates
        {
        public:
            bool is_valid() const;

        public:
            boost::function
            <
                std::unique_ptr< std::istream >( const std::string& )
            > read_file;
            
            boost::function< std::string() > get_writable_path;
            
            boost::function< bool( const std::string& ) > create_directories;
            boost::function< bool( const std::string& ) > file_exists;
            boost::function< std::string( const std::string& ) > get_full_path;
        };
    }
}

#endif
