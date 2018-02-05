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
#ifndef ISCOOL_SOCIAL_DETAIL_LINK_PLATFORM_SERVICE_H
#define ISCOOL_SOCIAL_DETAIL_LINK_PLATFORM_SERVICE_H

#if defined __APPLE__
#include "TargetConditionals.h"
#endif

#if defined __ANDROID__
#include "iscool/social/android/link_service.h"
#elif ( TARGET_OS_IPHONE == 1 )
#include "iscool/social/ios/link_service.h"
#else
  #include "iscool/social/detail/mockup_link_service.h"
#endif

namespace iscool
{
    namespace social
    {
        namespace detail
        {
#if defined __ANDROID__
            typedef android::link_service link_platform_service;
#elif ( TARGET_OS_IPHONE == 1 )
            typedef ios::link_service link_platform_service;
#else
            typedef mockup_link_service link_platform_service;
#endif
        }
    }
}

#endif
