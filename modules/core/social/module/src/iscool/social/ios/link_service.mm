/* -*- mode: objc -*- */
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
#include "iscool/social/ios/link_service.h"

#include "iscool/ios/std_to_nsstring.h"

#import <UIKit/UIApplication.h>

namespace iscool
{
    namespace social
    {
        namespace ios
        {
            namespace detail
            {
                static void open_in_app
                ( const std::string& app_url, const std::string& fallback_url );
            }
        }
    }
}

void iscool::social::ios::link_service::open_in_facebook
( const std::string& page )
{
    NSString* const page_url
        ( iscool::ios::std_to_nsstring( "https://www.facebook.com/" + page ) );
    NSURL* const url( [ NSURL URLWithString: page_url ] );
    
    [ [ UIApplication sharedApplication] openURL: url ];
}

void iscool::social::ios::link_service::open_in_twitter
( const std::string& page )
{
    detail::open_in_app
        ( "twitter://user?screen_name=" + page, "https://twitter.com/" + page );
}

void iscool::social::ios::detail::open_in_app
( const std::string& app_url, const std::string& fallback_url )
{
    NSString* const ns_app_url( iscool::ios::std_to_nsstring( app_url ) );
    NSURL* const native_app_url( [ NSURL URLWithString: ns_app_url ] );
    
    if ( [ [ UIApplication sharedApplication] openURL: native_app_url ] == NO )
    {
        NSString* const ns_fallback_url
            ( iscool::ios::std_to_nsstring( fallback_url ) );
        NSURL* const native_fallback_url
            ( [ NSURL URLWithString: ns_fallback_url ] );

        [ [ UIApplication sharedApplication] openURL: native_fallback_url ];
    }
}
