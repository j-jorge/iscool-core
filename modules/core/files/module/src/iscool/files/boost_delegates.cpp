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
#include "iscool/files/boost_delegates.h"

#include <boost/filesystem.hpp>

#include <fstream>

iscool::files::file_system_delegates
iscool::files::boost_filesystem_delegates
( const std::string& root, const std::string& writable_path )
{
    iscool::files::file_system_delegates result;
    
    result.read_file =
        [ root ]( const std::string& path )
        -> std::unique_ptr< std::istream >
    {
        return std::unique_ptr< std::istream >
            ( new std::ifstream( root + "/" + path ) );
    };
    
    result.get_writable_path =
        [ writable_path ]() -> std::string
    {
        return writable_path;
    };

    result.create_directories =
        []( const std::string& path ) -> bool
    {
        boost::system::error_code error;
        boost::filesystem::path full_puth( path );

        return boost::filesystem::create_directories
            ( full_puth.parent_path(), error );
    };
        
    result.file_exists =
        []( const std::string& path ) -> bool
    {
        boost::filesystem::path full_puth( path );
        return boost::filesystem::exists( full_puth );
    };

    result.get_full_path =
        [ root ]( const std::string& path ) -> std::string
    {
        if ( path.empty() || ( path[ 0 ] != '/' ) )
            return root + "/" + path;

        return path;
    };

    return result;
}

