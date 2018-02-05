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
#include "iscool/profile/profiler.h"
#include "iscool/profile/setup.h"

#include "iscool/time/now.h"

#include "iscool/test/equal_collections.h"
#include "iscool/test/no_crash.h"

TEST( iscool_profile, profiler_not_initialized )
{
    iscool::profile::profiler profiler( "test" );
    profiler.start();
    ASSERT_NO_CRASH( profiler.end() );
}

TEST( iscool_profile, profiler_started )
{
    iscool::profile::profiler profiler( "test" );
    EXPECT_FALSE( profiler.started() );
    profiler.start();
    EXPECT_TRUE( profiler.started() );
    profiler.end();
    EXPECT_FALSE( profiler.started() );
    profiler.start();
    EXPECT_TRUE( profiler.started() );
    profiler.end();
    EXPECT_FALSE( profiler.started() );
}

TEST( iscool_profile, profiler_output_function_called )
{
    bool called( false );
    iscool::profile::initialize
        ( [ &called ] ( iscool::profile::profile_data data ) -> void
          {
              called = true;
          } );

    iscool::profile::profiler profiler( "test" );
    EXPECT_FALSE( called );
    profiler.start();
    EXPECT_FALSE( called );
    profiler.end();
    EXPECT_TRUE( called );

    called = false;
    profiler.start();
    EXPECT_FALSE( called );
    profiler.end();
    EXPECT_TRUE( called );
    
    iscool::profile::finalize();
}

TEST( iscool_profile, profiler_name )
{
    std::string output;
    iscool::profile::initialize
        ( [ &output ] ( iscool::profile::profile_data data ) -> void
          {
              output = data.name;
          } );

    {
        iscool::profile::profiler profiler( "name" );
        profiler.start();
        profiler.end();

        EXPECT_EQ( "name", output );
        output = std::string();
    }

    {
        iscool::profile::profiler profiler( "name" );
        profiler.append_tag( "tag" );
        profiler.start();
        profiler.end();

        EXPECT_EQ( "name", output );
    }    
    iscool::profile::finalize();
}

TEST( iscool_profile, profiler_tags )
{
    typedef std::vector< std::string > tag_list;
   tag_list output;
    iscool::profile::initialize
        ( [ &output ] ( iscool::profile::profile_data data ) -> void
          {
              output = data.tags;
          } );

    {
        iscool::profile::profiler profiler( "name" );
        profiler.start();
        profiler.end();

        iscool::test::assert_equal_collections( output, tag_list() );
        output.clear();
    }

    {
        iscool::profile::profiler profiler( "name" );
        profiler.append_tag( "1" );
        profiler.start();
        profiler.append_tag( "2" );
        profiler.end();

        iscool::test::assert_equal_collections
            ( output, tag_list( { "1", "2" } ) );
        output.clear();

        profiler.append_tag( "3" );
        profiler.start();
        profiler.append_tag( "4" );
        profiler.end();

        iscool::test::assert_equal_collections
            ( output, tag_list( { "1", "2", "3", "4" } ) );
        output.clear();

        profiler.clear_tags();
        profiler.start();
        profiler.end();
        iscool::test::assert_equal_collections( output, tag_list() );
        output.clear();

        profiler.append_tag( "tag" );
        profiler.start();
        profiler.end();
        iscool::test::assert_equal_collections( output, tag_list( { "tag" } ) );
        output.clear();
    }    

    iscool::profile::finalize();
}

TEST( iscool_profile, profiler_duration )
{
    std::chrono::milliseconds output_start( 0 );
    std::chrono::milliseconds output_end( 0 );
    iscool::profile::initialize
        ( [ &output_start, &output_end ]
          ( iscool::profile::profile_data data ) -> void
          {
              output_start = data.start;
              output_end = data.end;
          } );

    iscool::profile::profiler profiler( "name" );
    const std::chrono::milliseconds start
        ( iscool::time::now<std::chrono::milliseconds>() );
    profiler.start();

    static constexpr useconds_t milliseconds( 1000 );
    usleep( 20 * milliseconds );
    
    const std::chrono::milliseconds end
        ( iscool::time::now<std::chrono::milliseconds>() );
    profiler.end();

    EXPECT_EQ( output_start, start );
    EXPECT_EQ( output_end, end );

    iscool::profile::finalize();
}
