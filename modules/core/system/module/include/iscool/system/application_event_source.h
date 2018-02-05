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
#ifndef ISCOOL_SYSTEM_APPLICATION_EVENT_SOURCE_H
#define ISCOOL_SYSTEM_APPLICATION_EVENT_SOURCE_H

#include "iscool/signals/declare_signal.h"

namespace iscool
{
    namespace system
    {
        class application_event_source
        {
            DECLARE_VOID_SIGNAL( enter_background, _enter_background );
            DECLARE_VOID_SIGNAL( enter_foreground, _enter_foreground );

        public:
            application_event_source();
            ~application_event_source();
            
            void dispatch_enter_background() const;
            void dispatch_enter_foreground() const;
        };
    }
}

#endif
