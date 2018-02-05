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
#include "iscool/time/round.h"

#include "gtest/gtest.h"

TEST( iscool_time, round )
{
    typedef std::chrono::duration< std::size_t, std::ratio< 1 > > unit;
    typedef std::chrono::duration< std::size_t, std::ratio< 2 > > pair;
    typedef std::chrono::duration< std::size_t, std::ratio< 3 > > triple;
    typedef std::chrono::duration< std::size_t, std::ratio< 5 > > quinte;

    EXPECT_EQ( unit( 2 ), iscool::time::round< unit >( pair( 1 ) ) );
    EXPECT_EQ( unit( 4 ), iscool::time::round< unit >( pair( 2 ) ) );
    EXPECT_EQ( triple( 1 ), iscool::time::round< triple >( pair( 1 ) ) );

    EXPECT_EQ( unit( 3 ), iscool::time::round< unit >( triple( 1 ) ) );
    EXPECT_EQ( unit( 6 ), iscool::time::round< unit >( triple( 2 ) ) );
    EXPECT_EQ( pair( 2 ), iscool::time::round< pair >( triple( 1 ) ) );
    EXPECT_EQ( pair( 3 ), iscool::time::round< pair >( triple( 2 ) ) );

    EXPECT_EQ( pair( 2 ), iscool::time::round< pair >( quinte( 1 ) ) );

}
