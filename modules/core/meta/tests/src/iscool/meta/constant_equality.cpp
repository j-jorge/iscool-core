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
#include "iscool/meta/constant_equality.h"

#include "gtest/gtest.h"

TEST( iscool_meta_constant_equality, int )
{
    const int a( 24 );
    const int b( 42 );

    EXPECT_TRUE( constant_equality( 24 )( 24 ) );
    EXPECT_TRUE( constant_equality( 24 )( a ) );
    EXPECT_TRUE( constant_equality( a )( 24 ) );
    EXPECT_TRUE( constant_equality( a )( a ) );
    EXPECT_FALSE( constant_equality( a )( b ) );
    EXPECT_FALSE( constant_equality( b )( a ) );
}
