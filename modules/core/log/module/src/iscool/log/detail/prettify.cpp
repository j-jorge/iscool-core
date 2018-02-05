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
#include "iscool/log/detail/prettify.h"
#include "iscool/log/nature/error.h"
#include "iscool/log/nature/nature.h"
#include "iscool/log/nature/warning.h"

#include <regex>

std::string iscool::log::detail::prettify( const std::string& message )
{
    static const std::string reset( "\33[0m" );
    static const std::string bold( "\33[1m" );
    static const std::string red( "\33[31m" );
    static const std::string yellow( "\33[33m" );
    static const std::string blue( "\33[34m" );
    static const std::string magenta( "\33[35m" );

    static const std::regex prefix
        ( "^(\\[[^\\]]+\\])(\\[[^\\]]+\\])(\\[[^\\]]+\\]) " );

    std::string result;
    std::string remaining;
    
    std::smatch match;

    if ( std::regex_search( message, match, prefix ) )
    {
        const std::string nature( match[ 1 ].str() );
        
        if ( nature == "[" + iscool::log::nature::error().string() + "]" )
            result += bold + red;
        else if
            ( nature == "[" + iscool::log::nature::warning().string() + "]" )
            result += bold + yellow;
        else
            result += bold;
        
        result += nature + reset; 

        result += blue + match[ 2 ].str() + match[ 3 ].str() + reset + ' ';
        remaining = match.suffix().str();
    }
    else
        remaining = message;
    
    static const std::regex type_name( "^[^:]*::[^: ]+" );

    if ( std::regex_search( remaining, match, type_name ) )
    {
        result +=
            match.prefix().str() + magenta + bold + match[ 0 ].str() + reset;
        remaining =  match.suffix().str();
    }

    static const std::regex key_value( "([^= ]+)=([^ ]+)" );

    while( std::regex_search( remaining, match, key_value ) )
    {
        result +=
            match.prefix().str() + bold + match[ 1 ].str()
            + reset + '=' + blue + bold + match[ 2 ].str() + reset;
        remaining = match.suffix();
    }

    static const std::regex string( "'[^']+'" );

    while( std::regex_search( remaining, match, string ) )
    {
        result +=
            match.prefix().str() + red + match[ 0 ].str() + reset;
        remaining = match.suffix();
    }
    
    result += remaining;
    
    return result;
}
