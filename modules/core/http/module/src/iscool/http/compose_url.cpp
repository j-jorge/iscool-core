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
#include "iscool/http/compose_url.h"

#include "iscool/http/url_encode.h"

std::string iscool::http::compose_url
( const std::string& root, const std::vector< query_parameter >& parameters )
{
    if( parameters.empty() )
        return root;

    std::string result( root + "?" );

    const auto eit( parameters.end() );
    auto query( parameters.begin() );

    result += query->key + "=" + url_encode( query->value );

    for( ++query; query != eit; ++query )
        result += "&" + query->key + "=" + url_encode( query->value );

    return result;
}
