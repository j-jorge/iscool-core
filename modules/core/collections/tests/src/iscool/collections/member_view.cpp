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
#include "iscool/collections/member_view.h"

#include <gtest/gtest.h>

namespace iscool
{
    namespace collections
    {
        namespace test
        {
            struct item
            {
                item( int value )
                    : field( value )
                {

                }

                int const_getter() const
                {
                    return field;
                }

                int field;
            };
        }
    }
}

TEST( iscool_collections_member_view, empty_field )
{
    const std::vector< iscool::collections::test::item > items( {} );

    const std::vector< int > view
        ( iscool::collections::member_view
          ( items, &iscool::collections::test::item::field ) );

    EXPECT_TRUE( view.empty() );
}

TEST( iscool_collections_member_view, empty_const_getter )
{
    const std::vector< iscool::collections::test::item > items( {} );

    const std::vector< int > view
        ( iscool::collections::member_view
          ( items, &iscool::collections::test::item::const_getter ) );

    EXPECT_TRUE( view.empty() );
}

TEST( iscool_collections_member_view, not_empty_field )
{
    const std::vector< iscool::collections::test::item > items( { 9, 5, 8 } );

    const std::vector< int > view
        ( iscool::collections::member_view
          ( items, &iscool::collections::test::item::field ) );

    EXPECT_EQ( items.size(), view.size() );
    EXPECT_EQ( items[ 0 ].field, view[ 0 ] );
    EXPECT_EQ( items[ 1 ].field, view[ 1 ] );
    EXPECT_EQ( items[ 2 ].field, view[ 2 ] );
}

TEST( iscool_collections_member_view, not_empty_const_getter )
{
    const std::vector< iscool::collections::test::item > items( { 9, 5, 8 } );

    const std::vector< int > view
        ( iscool::collections::member_view
          ( items, &iscool::collections::test::item::const_getter ) );

    EXPECT_EQ( items.size(), view.size() );
    EXPECT_EQ( items[ 0 ].const_getter(), view[ 0 ] );
    EXPECT_EQ( items[ 1 ].const_getter(), view[ 1 ] );
    EXPECT_EQ( items[ 2 ].const_getter(), view[ 2 ] );
}
