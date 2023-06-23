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
#ifndef ISCOOL_NOTIFICATION_DETAIL_PLATFORM_SERVICE_H
#define ISCOOL_NOTIFICATION_DETAIL_PLATFORM_SERVICE_H

#if defined __APPLE__
  #include "TargetConditionals.h"
#endif

#if defined __ANDROID__
  #include <iscool/notification/android/service.hpp>
#elif (TARGET_OS_IPHONE == 1)
  #include <iscool/notification/ios/service.hpp>
#else
  #include <iscool/notification/detail/mockup_service.hpp>
#endif

namespace iscool
{
  namespace notification
  {
    namespace detail
    {
#if defined __ANDROID__
      typedef android::service platform_service;
#elif (TARGET_OS_IPHONE == 1)
      typedef ios::service platform_service;
#else
      typedef detail::mockup_service platform_service;
#endif
    }
  }
}

#endif
