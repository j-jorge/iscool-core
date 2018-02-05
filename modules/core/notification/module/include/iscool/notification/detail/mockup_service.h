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
#ifndef ISCOOL_NOTIFICATION_DETAIL_MOCKUP_SERVICE_H
#define ISCOOL_NOTIFICATION_DETAIL_MOCKUP_SERVICE_H

#include <chrono>
#include <string>

namespace iscool
{
    namespace notification
    {
        namespace detail
        {
            class mockup_service
            {
            public:
                void enable_notifications();
                bool are_notifications_enabled() const;

                void schedule
                ( std::size_t id,
                  const std::chrono::seconds& delay,
                  const std::string& title,
                  const std::string& message );

                void cancel_all();
            };
        }
    }
}

#endif
