// SPDX-License-Identifier: Apache-2.0
#include <iscool/system/keep_screen_on.hpp>

#include <iscool/log/console_log.hpp>

void iscool::system::keep_screen_on(bool keep_on)
{
  ic_console_log("iscool::system", "keep_screen_on={}", keep_on);
}
