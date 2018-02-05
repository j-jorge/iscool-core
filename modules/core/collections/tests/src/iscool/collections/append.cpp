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
#include "iscool/collections/append.h"

#include "iscool/test/equal_collections.h"

#include "gtest/gtest.h"

#include <list>
#include <vector>

TEST( iscool_collections_append, empty_vectors )
{
    std::vector<int> output;
    std::vector<int> input;

    iscool::collections::append( output, input );

    EXPECT_TRUE( output.empty() );
}

TEST( iscool_collections_append, empty_vector_appended_to_non_empty_vector )
{
    std::vector<int> output = {{ 3, 1, 2 }};
    std::vector<int> input;

    const std::vector<int> expected_result( output );

    iscool::collections::append( output, input );

    iscool::test::assert_equal_collections( output, expected_result );
}

TEST( iscool_collections_append, non_empty_vector_appended_to_empty_vector )
{
    std::vector<int> output;
    std::vector<int> input = {{ 3, 1, 2 }};

    const std::vector<int> expected_result( input );

    iscool::collections::append( output, input );

    iscool::test::assert_equal_collections( output, expected_result );
}

TEST( iscool_collections_append, non_empty_vector_appended_to_non_empty_vector )
{
    std::vector<int> output = {{ 5, 3, 4 }};
    std::vector<int> input = {{ 3, 1, 2 }};

    const std::vector<int> expected_result( {{ 5, 3, 4, 3, 1, 2 }} );

    iscool::collections::append( output, input );

    iscool::test::assert_equal_collections( output, expected_result );
}

TEST( iscool_collections_append, vector_and_list )
{
    std::vector<int> output = { 1 };
    std::list<int> input = { 2 };

    const std::vector<int> expected_result( {{ 1, 2 }} );

    iscool::collections::append( output, input );

    iscool::test::assert_equal_collections( output, expected_result );
}

TEST( iscool_collections_append, list_and_vector )
{
    std::list<int> output = { 1 };
    std::vector<int> input = { 2 };

    const std::vector<int> expected_result( {{ 1, 2 }} );

    iscool::collections::append( output, input );

    iscool::test::assert_equal_collections( output, expected_result );
}

TEST( iscool_collections_append, int_list_and_float_vector )
{
    std::list<int> output = { 1 };
    std::vector<float> input = { 2.5 };

    const std::vector<int> expected_result( {{ 1, 2 }} );

    iscool::collections::append( output, input );

    iscool::test::assert_equal_collections( output, expected_result );
}

TEST( iscool_collections_append, float_list_and_int_vector )
{
    std::list<float> output = { 1.5 };
    std::vector<int> input = { 2 };

    const std::vector<float> expected_result( {{ 1.5, 2 }} );

    iscool::collections::append( output, input );

    iscool::test::assert_equal_collections( output, expected_result );
}

