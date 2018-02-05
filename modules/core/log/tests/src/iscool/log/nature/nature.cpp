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
#include "iscool/log/nature/nature.h"

#include <gtest/gtest.h>

TEST( iscool_log_nature_nature, getters )
{
    const iscool::log::nature::nature nature( "test" );

    EXPECT_EQ( "test", nature.string() );
    EXPECT_EQ( nature, nature );
    EXPECT_NE( iscool::log::nature::nature(), nature );
    EXPECT_NE( iscool::log::nature::nature( "nope" ), nature );
}

TEST( iscool_log_nature_nature, copy )
{
    const iscool::log::nature::nature nature( "N" );
    const iscool::log::nature::nature copy( nature );

    EXPECT_EQ( "N", copy.string() );
    EXPECT_EQ( nature, copy );
}

TEST( iscool_log_nature_nature, assignment )
{
    iscool::log::nature::nature copy;
    const iscool::log::nature::nature nature( "N" );

    copy = nature;
    
    EXPECT_EQ( "N", copy.string() );
    EXPECT_EQ( nature, copy );
}
