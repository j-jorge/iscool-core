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
#include "iscool/http/request.h"
#include "iscool/http/setup.h"
#include "iscool/http/json/send.h"

#include "iscool/none.h"
#include "iscool/optional.h"
#include "iscool/optional.impl.tpp"

#include "gtest/gtest.h"

#include <json/reader.h>

class json_send_mockup
{
public:
    json_send_mockup();
    ~json_send_mockup();

    iscool::signals::shared_connection_set get( const std::string& url );
    iscool::signals::shared_connection_set
    post( const std::string& url, const Json::Value& body );
    
    void dispatch_response( int code, const std::string& body );
    std::string error_string() const;

public:
    iscool::optional< iscool::http::request > _request;
    iscool::optional< Json::Value > _last_result;
    iscool::optional< std::vector< char > > _last_error;
};

json_send_mockup::json_send_mockup()
{
    auto request_handler
        ( [ this ]( const iscool::http::request& request ) -> void
          {
              _request = request;
          } );
    
    iscool::http::initialize( request_handler );
}

json_send_mockup::~json_send_mockup()
{
    iscool::http::finalize();
}

iscool::signals::shared_connection_set
json_send_mockup::get( const std::string& url )
{
    auto on_result
        ( [ this ]( Json::Value result ) -> void
          {
              _last_error = iscool::none;
              _last_result = result;
          } );

    auto on_error
        ( [ this ]( std::vector< char > error ) -> void
          {
              _last_result = iscool::none;
              _last_error = error;
          } );
    
    return iscool::http::json::get( url, on_result, on_error );
}

iscool::signals::shared_connection_set json_send_mockup::post
( const std::string& url, const Json::Value& body )
{
    auto on_result
        ( [ this ]( Json::Value result ) -> void
          {
              _last_error = iscool::none;
              _last_result = result;
          } );

    auto on_error
        ( [ this ]( std::vector< char > error ) -> void
          {
              _last_result = iscool::none;
              _last_error = error;
          } );
    
    return iscool::http::json::post( url, body, on_result, on_error );
}

void
json_send_mockup::dispatch_response( int code, const std::string& body )
{
    assert( _request );
    
    _request->get_response_handler()
        ( iscool::http::response
          ( code, std::vector< char >( body.begin(), body.end() ) ) );
}

std::string json_send_mockup::error_string() const
{
    assert( _last_error );
    return std::string( _last_error->begin(), _last_error->end() );
}

TEST( iscool_http_json_send_test, get_result )
{
    json_send_mockup mockup;
    
    const std::string url( "http://www.example.org" );
    const iscool::signals::shared_connection_set connections
        ( mockup.get( url ) );
    
    ASSERT_TRUE( !!mockup._request );
    EXPECT_EQ( iscool::http::request::type::get, mockup._request->get_type() );
    EXPECT_EQ( url, mockup._request->get_url() );

    Json::Value response;
    response[ "string" ] = "yep";
    response[ "number" ] = 24;
    
    mockup.dispatch_response( 200, response.toStyledString() );

    ASSERT_TRUE( !!mockup._last_result );
    EXPECT_FALSE( !!mockup._last_error );
    EXPECT_TRUE( *mockup._last_result == response );
}

TEST( iscool_http_json_send_test, get_empty_result )
{
    json_send_mockup mockup;
    
    const std::string url( "http://www.example.org" );
    const iscool::signals::shared_connection_set connections
        ( mockup.get( url ) );
    
    ASSERT_TRUE( !!mockup._request );
    EXPECT_EQ( iscool::http::request::type::get, mockup._request->get_type() );
    EXPECT_EQ( url, mockup._request->get_url() );

    mockup.dispatch_response( 200, std::string() );

    ASSERT_TRUE( !!mockup._last_result );
    EXPECT_FALSE( !!mockup._last_error );
    EXPECT_TRUE( mockup._last_result->isNull() );
}

TEST( iscool_http_json_send_test, get_error )
{
    json_send_mockup mockup;
    
    const std::string url( "http://www.example.org" );
    const iscool::signals::shared_connection_set connections
        ( mockup.get( url ) );
    const std::string response( "{ \"string\": yep, \"number\": 24 }" );
    
    mockup.dispatch_response( 300, response );

    ASSERT_TRUE( !!mockup._last_error );
    EXPECT_FALSE( !!mockup._last_result );
    EXPECT_EQ( response, mockup.error_string() );
}

TEST( iscool_http_json_send_test, post_result )
{
    json_send_mockup mockup;
    
    const std::string url( "http://www.example.org" );
    Json::Value body;
    body[ 0 ] = "yep";
    body[ 1 ] = 24;
    
    const iscool::signals::shared_connection_set connections
        ( mockup.post( url, body ) );
    
    ASSERT_TRUE( !!mockup._request );
    EXPECT_EQ( iscool::http::request::type::post, mockup._request->get_type() );
    EXPECT_EQ( url, mockup._request->get_url() );

    Json::Value request_body;
    Json::Reader reader;
    EXPECT_TRUE( reader.parse( mockup._request->get_body(), request_body ) );
    EXPECT_TRUE( request_body == body );

    const std::vector< std::string > headers( mockup._request->get_headers() );

    ASSERT_FALSE( headers.empty() );
    bool content_type_set( false );
    bool accept_set( false );

    for( const std::string& h : headers )
    {
        if ( h.find( "Content-Type:" ) == 0 )
        {
            if ( h.find( "application/json" ) != std::string::npos )
                content_type_set = true;
        }
        else if ( h.find("Accept:") == 0 )
        {
            if ( h.find( "application/json" ) != std::string::npos )
                accept_set = true;
        }
    }

    EXPECT_TRUE( content_type_set );
    EXPECT_TRUE( accept_set );
    
    const Json::Value response( 2.4 );
    
    mockup.dispatch_response( 200, response.toStyledString() );

    ASSERT_TRUE( !!mockup._last_result );
    EXPECT_FALSE( mockup._last_error );
    EXPECT_TRUE( *mockup._last_result == response );
}

TEST( iscool_http_json_send_test, post_empty_result )
{
    json_send_mockup mockup;
    
    const std::string url( "http://www.example.org" );
    Json::Value body;
    body[ 0 ] = "yep";
    body[ 1 ] = 24;
    
    const iscool::signals::shared_connection_set connections
        ( mockup.post( url, body ) );
    
    ASSERT_TRUE( !!mockup._request );
    EXPECT_EQ( iscool::http::request::type::post, mockup._request->get_type() );
    EXPECT_EQ( url, mockup._request->get_url() );

    mockup.dispatch_response( 200, std::string() );

    ASSERT_TRUE( !!mockup._last_result );
    EXPECT_FALSE( mockup._last_error );
    EXPECT_TRUE( mockup._last_result->isNull() );
}

TEST( iscool_http_json_send_test, post_error )
{
    json_send_mockup mockup;
    
    const std::string url( "http://www.example.org" );
    Json::Value body( "24" );
    
    const iscool::signals::shared_connection_set connections
        ( mockup.post( url, body ) );
    const std::string response( "system failure" );
    
    mockup.dispatch_response( 300, response );

    ASSERT_TRUE( !!mockup._last_error );
    EXPECT_FALSE( mockup._last_result );
    EXPECT_EQ( response, mockup.error_string() );
}
