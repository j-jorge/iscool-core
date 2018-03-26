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
#ifndef ISCOOL_SYSTEM_DEVICE_TIME_TPP
#define ISCOOL_SYSTEM_DEVICE_TIME_TPP

#include "iscool/system/detail/device_time_milliseconds.h"

#include <chrono>

template< typename Duration >
Duration iscool::system::device_time()
{
    return
        std::chrono::duration_cast< Duration >
        ( detail::device_time_milliseconds() );
}

#endif
