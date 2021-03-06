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
#include "iscool/optional.h"
#include "iscool/error/synopsis.h"
#include "iscool/log/causeless_log.h"
#include "iscool/log/log_error.h"
#include "iscool/log/message_delegates_registry.h"
#include "iscool/log/setup.h"
#include "iscool/log/nature/nature.h"

#include <boost/bind.hpp>

#include <gtest/gtest.h>

class iscool_log_test:
    public ::testing::Test
{
public:
    iscool_log_test();
    ~iscool_log_test();

protected:
    iscool::log::nature::nature _nature;
    iscool::log::context _context;
    std::string _message;

    iscool::optional< iscool::error::synopsis > _error;

private:
    void print_message
    ( const iscool::log::nature::nature& nature,
      const iscool::log::context& context,
      const std::string& message );

    void print_error
    ( const iscool::log::context& context,
      const iscool::error::synopsis& error );

private:
    std::size_t _delegates_id;
};
            
iscool_log_test::iscool_log_test()
{
    iscool::log::message_delegates delegates;
    delegates.print_message =
        boost::bind
        ( &iscool_log_test::print_message, this, _1, _2, _3 );
    delegates.print_error =
        boost::bind
        ( &iscool_log_test::print_error, this, _1, _2 );

    iscool::log::initialize();
    _delegates_id = iscool::log::register_delegates( delegates );
}

iscool_log_test::~iscool_log_test()
{
    iscool::log::unregister_delegates( _delegates_id );
    iscool::log::finalize();
}

void iscool_log_test::print_message
( const iscool::log::nature::nature& nature,
  const iscool::log::context& context, const std::string& message )
{
    _nature = nature;
    _context = context;
    _message = message;
}

void iscool_log_test::print_error
( const iscool::log::context& context, const iscool::error::synopsis& error )
{
    _context = context;
    _error = error;
}

TEST_F( iscool_log_test, log )
{
    const iscool::log::nature::nature nature( "nature" );
    
    const std::size_t line ( __LINE__ ); ic_log
                                             ( nature, "reporter", "origin",
                                               "message %1%: %2%", 24, 42 );
    
    EXPECT_EQ( nature, _nature );
    EXPECT_EQ( "reporter", _context.get_reporter() );
    EXPECT_EQ( "origin", _context.get_origin() );
    EXPECT_EQ( __FILE__, _context.get_file() );
    EXPECT_EQ( line, _context.get_line() );
    EXPECT_EQ( "message 24: 42", _message );

    EXPECT_FALSE( !!_error );
}

TEST_F( iscool_log_test, causeless_log )
{
    const iscool::log::nature::nature nature( "log-nature" );
    
     const std::size_t line( __LINE__ ); ic_causeless_log
                                             ( nature, "log-reporter",
                                               "msg %1%", 94 );
    
    EXPECT_EQ( nature, _nature );
    EXPECT_EQ( "log-reporter", _context.get_reporter() );
    EXPECT_FALSE( _context.get_origin().empty() );
    EXPECT_EQ( __FILE__, _context.get_file() );
    EXPECT_EQ( line, _context.get_line() );
    EXPECT_EQ( "msg 94", _message );

    EXPECT_FALSE( !!_error );
}

TEST_F( iscool_log_test, log_error )
{
    const iscool::error::synopsis error( 24, "category", "title", "msg" );

    const std::size_t line( __LINE__ ); ic_log_error
                                            ( "reporter", "origin", error );
    
    EXPECT_EQ( "reporter", _context.get_reporter() );
    EXPECT_EQ( "origin", _context.get_origin() );
    EXPECT_EQ( __FILE__, _context.get_file() );
    EXPECT_EQ( line, _context.get_line() );

    EXPECT_TRUE( !!_error );

    EXPECT_EQ( error.get_code(), _error->get_code() );
    EXPECT_EQ( error.get_category(), _error->get_category() );
    EXPECT_EQ( error.get_title(), _error->get_title() );
    EXPECT_EQ( error.get_message(), _error->get_message() );
}
