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
#pragma once

#include <iscool/i18n/gettext.hpp>
#include <iscool/time/days.hpp>
#include <iscool/time/round.hpp>

#include <cassert>
#include <format>

template <class Rep, class Period>
std::string iscool::i18n::relative_past_duration(
    const std::chrono::duration<Rep, Period>& duration)
{
  assert(duration.count() >= 0);

  if (duration == std::chrono::milliseconds::zero())
    return ic_gettext("now");

  std::size_t count;
  const char* format;

  if (duration < std::chrono::seconds(1))
    {
      count = time::round<std::chrono::milliseconds>(duration).count();
      format = ic_gettext("{} ms. ago");
    }
  else if (duration < std::chrono::minutes(1))
    {
      count = time::round<std::chrono::seconds>(duration).count();
      format = ic_gettext("{} s. ago");
    }
  else if (duration < std::chrono::hours(1))
    {
      count = time::round<std::chrono::minutes>(duration).count();
      format = ic_gettext("{} min. ago");
    }
  else if (duration < iscool::time::days(1))
    {
      count = time::round<std::chrono::hours>(duration).count();
      format = ic_gettext("{} h. ago");
    }
  else
    {
      count = time::round<iscool::time::days>(duration).count();

      if (count == 1)
        format = ic_gettext("{} day ago");
      else
        format = ic_gettext("{} days ago");
    }

  return std::vformat(format, std::make_format_args(count));
}
