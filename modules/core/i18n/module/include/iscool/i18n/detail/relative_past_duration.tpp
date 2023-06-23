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
#ifndef ISCOOL_I18N_RELATIVE_PAST_DURATION_TPP
#define ISCOOL_I18N_RELATIVE_PAST_DURATION_TPP

#include "iscool/i18n/gettext.h"
#include "iscool/time/days.h"
#include "iscool/time/round.h"

#include <boost/format.hpp>

#include <cassert>

template <class Rep, class Period>
std::string iscool::i18n::relative_past_duration(
    const std::chrono::duration<Rep, Period>& duration)
{
  assert(duration.count() >= 0);

  if (duration == std::chrono::milliseconds::zero())
    return ic_gettext("now");

  std::size_t count;
  std::string format;

  if (duration < std::chrono::seconds(1))
    {
      count = time::round<std::chrono::milliseconds>(duration).count();
      format = ic_gettext("%d ms. ago");
    }
  else if (duration < std::chrono::minutes(1))
    {
      count = time::round<std::chrono::seconds>(duration).count();
      format = ic_gettext("%d s. ago");
    }
  else if (duration < std::chrono::hours(1))
    {
      count = time::round<std::chrono::minutes>(duration).count();
      format = ic_gettext("%d min. ago");
    }
  else if (duration < iscool::time::days(1))
    {
      count = time::round<std::chrono::hours>(duration).count();
      format = ic_gettext("%d h. ago");
    }
  else
    {
      count = time::round<iscool::time::days>(duration).count();

      if (count == 1)
        format = ic_gettext("%d day ago");
      else
        format = ic_gettext("%d days ago");
    }

  return (boost::format(format) % count).str();
}

#endif
