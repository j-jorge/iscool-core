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
#ifndef ISCOOL_SYSTEM_APPLICATION_EVENTS_H
#define ISCOOL_SYSTEM_APPLICATION_EVENTS_H

#include "iscool/signals/connection.h"
#include "iscool/signals/void_signal_function.h"

namespace iscool
{
    namespace system
    {
        class application_event_source;

        class application_events
        {
        public:
            explicit application_events( application_event_source& source );
            
            iscool::signals::connection
            connect_to_enter_background
            ( iscool::signals::void_signal_function f ) const;
            
            iscool::signals::connection
            connect_to_enter_foreground
            ( iscool::signals::void_signal_function f ) const;
            
        private:
            application_event_source& _source;
        };
    }
}

#endif

