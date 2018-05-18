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
#include "iscool/files/default_file_system_delegates.h"

#include <boost/filesystem/operations.hpp>

#include <fstream>

iscool::files::default_file_system_delegates::default_file_system_delegates
( const std::string& root, const std::string& writable_path )
    : _root( root ),
      _writable_path( writable_path )
{

}

std::unique_ptr< std::istream >
iscool::files::default_file_system_delegates::read_file
( const std::string& path ) const
{
    return
        std::unique_ptr< std::istream >
        ( new std::ifstream( _root + "/" + path ) );
}
            
std::string
iscool::files::default_file_system_delegates::get_writable_path() const
{
    return _writable_path;
}

bool iscool::files::default_file_system_delegates::file_exists
( const std::string& path ) const
{
    return boost::filesystem::exists( path );
}

std::string iscool::files::default_file_system_delegates::get_full_path
( const std::string& path ) const
{
    return boost::filesystem::absolute( path, _root ).string();
}
