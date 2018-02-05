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
#include "iscool/signals/signal_collection.h"

#include "iscool/signals/get.h"
#include "iscool/signals/signal.impl.tpp"

#include <gtest/gtest.h>

TEST( iscool_signals_signal_collection, connect )
{
    iscool::signals::signal_collection
    <
        int,
        std::string,
        short,
        float
    > signals;

    int int_calls( 0 );
    int int_arg( 0 );
    iscool::signals::get< int >( signals ).connect
        ( [ &int_calls, &int_arg ]( int v ) -> void
          {
              ++int_calls;
              int_arg = v;
          } );

    int short_calls( 0 );
    short short_arg( 0 );
    iscool::signals::get< short >( signals ).connect
        ( [ &short_calls, &short_arg ]( short v ) -> void
          {
              ++short_calls;
              short_arg = v;
          } );

    int string_calls( 0 );
    std::string string_arg;
    iscool::signals::get< std::string >( signals ).connect
        ( [ &string_calls, &string_arg ]( std::string v ) -> void
          {
              ++string_calls;
              string_arg = v;
          } );

    int float_calls( 0 );
    float float_arg( 0 );
    iscool::signals::get< float >( signals ).connect
        ( [ &float_calls, &float_arg ]( float v ) -> void
          {
              ++float_calls;
              float_arg = v;
          } );

    iscool::signals::get< float >( signals )( 12 );
    EXPECT_EQ( 0, int_calls );
    EXPECT_EQ( 0, short_calls );
    EXPECT_EQ( 0, string_calls );
    EXPECT_EQ( 1, float_calls );
    EXPECT_EQ( 12.f, float_arg );

    iscool::signals::get< int >( signals )( 24 );
    EXPECT_EQ( 1, int_calls );
    EXPECT_EQ( 0, short_calls );
    EXPECT_EQ( 0, string_calls );
    EXPECT_EQ( 1, float_calls );
    EXPECT_EQ( 24, int_arg );

    iscool::signals::get< short >( signals )( 84 );
    EXPECT_EQ( 1, int_calls );
    EXPECT_EQ( 1, short_calls );
    EXPECT_EQ( 0, string_calls );
    EXPECT_EQ( 1, float_calls );
    EXPECT_EQ( 84, short_arg );

    iscool::signals::get< std::string >( signals )( "yep" );
    EXPECT_EQ( 1, int_calls );
    EXPECT_EQ( 1, short_calls );
    EXPECT_EQ( 1, string_calls );
    EXPECT_EQ( 1, float_calls );
    EXPECT_EQ( "yep", string_arg );
}
