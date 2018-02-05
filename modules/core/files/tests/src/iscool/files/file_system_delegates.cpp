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
#include "iscool/files/file_system_delegates.h"

#include "gtest/gtest.h"

TEST( iscool_files_file_system_delegates, is_valid )
{
    iscool::files::file_system_delegates delegates;
    EXPECT_FALSE( delegates.is_valid() );

    delegates.read_file =
        []( const std::string& ) -> std::unique_ptr< std::istream >
        {
            return nullptr;
        };
    EXPECT_FALSE( delegates.is_valid() );
    
    delegates.get_writable_path =
        []() -> std::string
        {
            return std::string();
        };
    EXPECT_FALSE( delegates.is_valid() );
    
    delegates.create_directories =
        []( const std::string& ) -> bool
        {
            return false;
        };
    EXPECT_FALSE( delegates.is_valid() );

    delegates.file_exists =
        []( const std::string& ) -> bool
        {
            return false;
        };
    EXPECT_FALSE( delegates.is_valid() );

    delegates.get_full_path =
        []( const std::string& ) -> std::string
        {
            return std::string();
        };
    EXPECT_TRUE( delegates.is_valid() );

    delegates.file_exists.clear();
    EXPECT_FALSE( delegates.is_valid() );
}
