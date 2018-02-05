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
#include "iscool/collections/make_array.h"

#include <gtest/gtest.h>

TEST( iscool_collections_make_array, make )
{
    const std::array< int, 4 > array
        ( iscool::collections::make_array( 2, 9, 2, 3 ) );
    
    EXPECT_EQ( 2, array[ 0 ] );
    EXPECT_EQ( 9, array[ 1 ] );
    EXPECT_EQ( 2, array[ 2 ] );
    EXPECT_EQ( 3, array[ 3 ] );
}
