/* -*- c++ -*- */
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
#include <iscool/system/detail/device_time_milliseconds.hpp>

#import <Foundation/Foundation.h>

std::chrono::milliseconds iscool::system::detail::device_time_milliseconds()
{
    NSDate* const source_date( [ NSDate date ] );
    NSTimeZone* const local_time_zone( [ NSTimeZone localTimeZone ] );
    const NSTimeInterval gmt_offset( [ local_time_zone secondsFromGMT ] );
    const NSTimeInterval time_interval
        ( [ source_date timeIntervalSinceReferenceDate ] + gmt_offset );
    NSDate* const gmt_date
        ( [ NSDate dateWithTimeIntervalSinceReferenceDate: time_interval ] );

    return std::chrono::milliseconds
        ( std::chrono::milliseconds::rep
          ( 1000 * [ gmt_date timeIntervalSince1970 ] ) );
}
