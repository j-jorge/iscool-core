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
#include <iscool/system/detail/haptic_feedback_mockup.hpp>

#include <iscool/log/console_log.hpp>

#include <cassert>
#include <string>

bool iscool::system::haptic_feedback::is_enabled() const
{
  return false;
}

void iscool::system::haptic_feedback::set_enabled(bool enabled)
{
  ic_console_log("iscool::system", "Set haptic feedback enabled: %1%.",
                 enabled ? "true" : "false");
}

void iscool::system::haptic_feedback::click()
{
  ic_console_log("iscool::system", "Haptic feedback: 'click'.");
}
