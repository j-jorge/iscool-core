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
#include <iscool/notification/detail/mockup_service.hpp>

#include <iscool/log/console_log.hpp>

void iscool::notification::detail::mockup_service::enable_notifications()
{
  ic_console_log("iscool::notification::service", "Enable notifications");
}

bool iscool::notification::detail::mockup_service::are_notifications_enabled()
    const
{
  ic_console_log("iscool::notification::service", "Test availability.");

  return true;
}

void iscool::notification::detail::mockup_service::schedule(
    std::size_t id, const std::chrono::seconds& delay,
    const std::string& title, const std::string& message)
{
  ic_console_log("iscool::notification::service",
                 "Schedule notification in {0} seconds:"
                 " id={1}, title='{2}', message='{3}'.",
                 delay.count(), id, title, message);
}

void iscool::notification::detail::mockup_service::cancel_all()
{
  ic_console_log("iscool::notification::service", "Cancel all.");
}
