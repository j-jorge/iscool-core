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
#include "iscool/http/json/send.h"

#include "iscool/http/send.h"

#include "iscool/json/parse_string.h"

namespace iscool
{
    namespace http
    {
        namespace json
        {
            namespace detail
            {
                static http::response_handler build_json_result_handler
                ( response_handler on_result, http::response_handler on_error );
            }
        }
    }
}

iscool::signals::shared_connection_set
iscool::http::json::get
( const std::string& url, response_handler on_result,
  http::response_handler on_error )
{
    const http::response_handler convert_result_to_json
        ( detail::build_json_result_handler( on_result, on_error ) );

    return http::get( url, convert_result_to_json, on_error );
}

iscool::signals::shared_connection_set
iscool::http::json::post
( const std::string& url, Json::Value body, response_handler on_result,
  http::response_handler on_error )
{
    const std::string body_data( body.toStyledString() );
    const http::response_handler convert_result_to_json
        ( detail::build_json_result_handler( on_result, on_error ) );

    std::vector< std::string > headers;
    headers.push_back( "Content-Type: application/json; charset=utf-8" );
    headers.push_back( "Accept: application/json" );

    return http::post
        ( url, headers, body_data, convert_result_to_json, on_error );
}

iscool::http::response_handler
iscool::http::json::detail::build_json_result_handler
( response_handler on_result, http::response_handler on_error )
{
    return [ on_result, on_error ] ( std::vector<char> response ) -> void
    {
        if ( response.empty() )
        {
            on_result( Json::nullValue );
            return;
        }
        
        const Json::Value result_value
            ( iscool::json::parse_string
              ( std::string( response.begin(), response.end() ) ) );

        if( result_value != Json::nullValue )
            on_result( result_value );
        else 
            on_error( response ); 
    }; 
}

