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
#include "iscool/social/ios/share_service.h"

#include "iscool/social/ios/present_activity_view_controller.h"

#include "iscool/ios/std_to_nsstring.h"

void
iscool::social::ios::share_service::share_message( const std::string& message )
{
    NSString* const message_item( iscool::ios::std_to_nsstring( message ) );
    present_activity_view_controller( @[ message_item ] );
}

void iscool::social::ios::share_service::share_file
( const std::string& file_name, const std::string& message )
{
    NSString* const file_path( iscool::ios::std_to_nsstring( file_name ) );
    NSURL* const file_url( [ NSURL fileURLWithPath: file_path ] );

    NSString* const message_item( iscool::ios::std_to_nsstring( message ) );

    present_activity_view_controller( @[ message_item, file_url ] );
}
