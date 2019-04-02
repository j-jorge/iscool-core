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
#include "iscool/style/deep_mutate.h"

#include "iscool/optional.impl.tpp"

#include <gtest/gtest.h>

TEST( iscool_style_deep_mutate, create_intermediate_styles )
{
    iscool::style::declaration style;

    const auto mutation
        ( []( iscool::style::declaration& s ) -> void
          {
              s.set_number( "value", 18 );
          } );

    const std::array< std::string, 3 > path{{ "a", "b", "c" }};
    iscool::style::deep_mutate( style, path, mutation );

    const iscool::optional< const iscool::style::declaration& > a
        ( style.get_declaration( "a" ) );
    ASSERT_TRUE( !!a );
    
    const iscool::optional< const iscool::style::declaration& > b
        ( a->get_declaration( "b" ) );
    ASSERT_TRUE( !!b );

    const iscool::optional< const iscool::style::declaration& > c
        ( b->get_declaration( "c" ) );
    ASSERT_TRUE( !!c );

    const iscool::optional< float > value( c->get_number( "value" ) );
    ASSERT_TRUE( !!value );

    EXPECT_EQ( 18, *value );
}

TEST( iscool_style_deep_mutate, keep_existing_styles )
{
    iscool::style::declaration c;
    c.set_number( "value", 24 );
    c.set_string( "string", "yep" );

    iscool::style::declaration b;
    b.set_declaration( "c", c );
    
    iscool::style::declaration a;
    a.set_declaration( "b", b );
    
    iscool::style::declaration style;
    style.set_declaration( "a", a );

    const auto mutation
        ( []( iscool::style::declaration& s ) -> void
          {
              s.set_number( "value", 18 );
          } );

    const std::array< std::string, 3 > path{{ "a", "b", "c" }};
    iscool::style::deep_mutate( style, path, mutation );

    const iscool::optional< const iscool::style::declaration& > sub_a
        ( style.get_declaration( "a" ) );
    ASSERT_TRUE( !!sub_a );
    
    const iscool::optional< const iscool::style::declaration& > sub_b
        ( sub_a->get_declaration( "b" ) );
    ASSERT_TRUE( !!sub_b );

    const iscool::optional< const iscool::style::declaration& > sub_c
        ( sub_b->get_declaration( "c" ) );
    ASSERT_TRUE( !!sub_c );

    const iscool::optional< std::string > string
        ( sub_c->get_string( "string" ) );
    ASSERT_TRUE( !!string );
    EXPECT_EQ( "yep", *string );
    
    const iscool::optional< float > value( sub_c->get_number( "value" ) );
    ASSERT_TRUE( !!value );
    EXPECT_EQ( 18, *value );
}

TEST( iscool_style_deep_mutate, modify_root )
{
    iscool::style::declaration style;

    const auto mutation
        ( []( iscool::style::declaration& s ) -> void
          {
              s.set_number( "value", 24 );
          } );

    const std::array< std::string, 0 > path{};
    iscool::style::deep_mutate( style, path, mutation );

    const iscool::optional< float > value( style.get_number( "value" ) );
    ASSERT_TRUE( !!value );
    EXPECT_EQ( 24, *value );
}
