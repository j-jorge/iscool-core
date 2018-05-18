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
#include "iscool/files/file_exists.h"
#include "iscool/files/get_full_path.h"
#include "iscool/files/get_writable_path.h"
#include "iscool/files/read_file.h"
#include "iscool/files/setup.h"

#include "iscool/files/test/file_system_delegates_mockup.h"

#include <gtest/gtest.h>

TEST( iscool_files, read_file )
{
    iscool::files::test::file_system_delegates_mockup delegates;
    iscool::files::initialize( delegates );

    std::string file_name;
    std::istream* stream( nullptr );

    delegates.read_file_impl =
        [ &file_name, &stream ]
        ( const std::string& name ) -> std::unique_ptr< std::istream >
        {
            file_name = name;
            stream = new std::istringstream();
            return std::unique_ptr< std::istream >( stream );
        };
    
    EXPECT_EQ( stream, iscool::files::read_file( "filename" ).get() );
    EXPECT_EQ( "filename", file_name );
    
    iscool::files::finalize();
}

TEST( iscool_files, get_writable_path )
{
    iscool::files::test::file_system_delegates_mockup delegates;
    iscool::files::initialize( delegates );

    delegates.get_writable_path_impl =
        []() -> std::string
        {
            return "the/path";
        };
    
    EXPECT_EQ( "the/path", iscool::files::get_writable_path() );
    
    iscool::files::finalize();
}

TEST( iscool_files, file_exists )
{
    iscool::files::test::file_system_delegates_mockup delegates;
    iscool::files::initialize( delegates );

    std::string arg;
    bool expected_result;
    
    delegates.file_exists_impl =
        [ &arg, &expected_result ]( const std::string& path ) -> bool
        {
            arg = path;
            return expected_result;
        };
    
    expected_result = true;
    EXPECT_EQ( expected_result, iscool::files::file_exists( "some/path" ) );
    EXPECT_EQ( "some/path", arg );

    expected_result = false;
    EXPECT_EQ( expected_result, iscool::files::file_exists( "some/path" ) );
    
    iscool::files::finalize();
}

TEST( iscool_files, get_full_path )
{
    iscool::files::test::file_system_delegates_mockup delegates;
    iscool::files::initialize( delegates );

    std::string arg;
    
    delegates.get_full_path_impl =
        [ &arg ]( const std::string& path ) -> std::string
        {
            arg = path;
            return "the/full/path";
        };
    
    EXPECT_EQ( "the/full/path", iscool::files::get_full_path( "some/path" ) );
    EXPECT_EQ( "some/path", arg );

    iscool::files::finalize();
}
