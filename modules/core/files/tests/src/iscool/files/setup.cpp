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
#include "iscool/files/create_directories.h"
#include "iscool/files/file_exists.h"
#include "iscool/files/get_full_path.h"
#include "iscool/files/get_writable_path.h"
#include "iscool/files/read_file.h"
#include "iscool/files/setup.h"

#include "iscool/files/test/empty_file_delegates.h"

#include "gtest/gtest.h"

TEST( iscool_files, read_file )
{
    iscool::files::file_system_delegates delegates
        ( iscool::files::test::create_empty_delegates() );
    std::string file_name;
    std::istream* stream( nullptr );

    delegates.read_file =
        [ &file_name, &stream ]
        ( const std::string& name ) -> std::unique_ptr< std::istream >
        {
            file_name = name;
            stream = new std::istringstream();
            return std::unique_ptr< std::istream >( stream );
        };
    
    iscool::files::initialize( delegates );

    EXPECT_EQ( stream, iscool::files::read_file( "filename" ).get() );
    EXPECT_EQ( "filename", file_name );
    
    iscool::files::finalize();
}

TEST( iscool_files, get_writable_path )
{
    iscool::files::file_system_delegates delegates
        ( iscool::files::test::create_empty_delegates() );

    delegates.get_writable_path =
        []() -> std::string
        {
            return "the/path";
        };
    
    iscool::files::initialize( delegates );

    EXPECT_EQ( "the/path", iscool::files::get_writable_path() );
    
    iscool::files::finalize();
}

TEST( iscool_files, create_directories )
{
    iscool::files::file_system_delegates delegates
        ( iscool::files::test::create_empty_delegates() );
    std::string arg;
    bool expected_result;
    
    delegates.create_directories =
        [ &arg, &expected_result ]( const std::string& path ) -> bool
        {
            arg = path;
            return expected_result;
        };
    
    iscool::files::initialize( delegates );

    expected_result = true;
    EXPECT_EQ( expected_result,
                iscool::files::create_directories( "some/path" ) );
    EXPECT_EQ( "some/path", arg );

    expected_result = false;
    EXPECT_EQ( expected_result,
                iscool::files::create_directories( "some/path" ) );
    
    iscool::files::finalize();
}

TEST( iscool_files, file_exists )
{
    iscool::files::file_system_delegates delegates
        ( iscool::files::test::create_empty_delegates() );
    std::string arg;
    bool expected_result;
    
    delegates.file_exists =
        [ &arg, &expected_result ]( const std::string& path ) -> bool
        {
            arg = path;
            return expected_result;
        };
    
    iscool::files::initialize( delegates );

    expected_result = true;
    EXPECT_EQ( expected_result, iscool::files::file_exists( "some/path" ) );
    EXPECT_EQ( "some/path", arg );

    expected_result = false;
    EXPECT_EQ( expected_result, iscool::files::file_exists( "some/path" ) );
    
    iscool::files::finalize();
}

TEST( iscool_files, get_full_path )
{
    iscool::files::file_system_delegates delegates
        ( iscool::files::test::create_empty_delegates() );
    std::string arg;
    
    delegates.get_full_path =
        [ &arg ]( const std::string& path ) -> std::string
        {
            arg = path;
            return "the/full/path";
        };
    
    iscool::files::initialize( delegates );

    EXPECT_EQ( "the/full/path", iscool::files::get_full_path( "some/path" ) );
    EXPECT_EQ( "some/path", arg );

    iscool::files::finalize();
}
