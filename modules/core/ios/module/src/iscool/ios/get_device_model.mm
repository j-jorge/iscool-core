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
#include "iscool/ios/get_device_model.h"

#include <sys/sysctl.h>

#include <cassert>
#include <vector>

std::string iscool::ios::get_device_model()
{
    std::size_t size;
    sysctlbyname( "hw.machine", nullptr, &size, nullptr, 0 );

    std::vector< char > result( size );
    sysctlbyname( "hw.machine", result.data(), &size, nullptr, 0 );
    assert( result.begin() != result.end() );

    return std::string( result.begin(), result.end() - 1 );
}
