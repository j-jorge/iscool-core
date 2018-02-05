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
#include "iscool/strings/vector_to_string.h"

#include "gtest/gtest.h"

TEST( iscool_strings_vector_to_string, empty )
{
    std::vector< int > v;
    EXPECT_EQ( "", iscool::strings::vector_to_string( v, ',' ) );
}

TEST( iscool_strings_vector_to_string, one )
{
    std::vector< int > v( { 2 } );
    EXPECT_EQ( "2", iscool::strings::vector_to_string( v, ',' ) );
}

TEST( iscool_strings_vector_to_string, two )
{
    std::vector< int > v( { 5, 4 } );
    EXPECT_EQ( "5,4", iscool::strings::vector_to_string( v, ',' ) );
}

TEST( iscool_strings_vector_to_string, strings )
{
    std::vector< std::string > v( { "abc", "def" } );
    EXPECT_EQ( "abc,def", iscool::strings::vector_to_string( v, ',' ) );
}

TEST( iscool_strings_vector_to_string, separator )
{
    std::vector< int > v( { 9, 32, 34, 8 } );
    EXPECT_EQ( "9:32:34:8", iscool::strings::vector_to_string( v, ':' ) );
}
