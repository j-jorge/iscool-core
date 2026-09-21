// SPDX-License-Identifier: Apache-2.0
#include <iscool/time/parse_timestamp.hpp>

#include <cassert>
#include <charconv>

/**
 * Hand-written parsing for timestamps, because Android does not provide
 * std::chrono::utc_clock nor std::chrono::parse at the time of this writing.
 */
bool iscool::time::parse_timestamp(std::chrono::system_clock::time_point& t,
                                   std::string_view s)
{
  if (s.size() < 20)
    return false;

  if ((s[4] != '-') || (s[7] != '-') || (s[10] != 'T') || (s[13] != ':')
      || (s[16] != ':') || ((s[19] != '.') && (s[19] != 'Z'))
      || (s.back() != 'Z'))
    return false;

  for (int i = 0; i != 4; ++i)
    if ((s[i] < '0') || (s[i] > '9'))
      return false;

  if ((s[5] < '0') || (s[5] > '1') || (s[6] < '0') || (s[6] > '9'))
    return false;

  if ((s[8] < '0') || (s[8] > '3') || (s[9] < '0') || (s[9] > '9'))
    return false;

  if ((s[11] < '0') || (s[11] > '5') || (s[12] < '0') || (s[12] > '9'))
    return false;

  if ((s[14] < '0') || (s[14] > '5') || (s[15] < '0') || (s[15] > '9'))
    return false;

  if ((s[17] < '0') || (s[17] > '5') || (s[18] < '0') || (s[18] > '9'))
    return false;

  const int year((s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10
                 + (s[3] - '0'));
  const int month((s[5] - '0') * 10 + (s[6] - '0'));
  const int day((s[8] - '0') * 10 + (s[9] - '0'));
  const int hours((s[11] - '0') * 10 + (s[12] - '0'));
  const int minutes((s[14] - '0') * 10 + (s[15] - '0'));
  const int seconds((s[17] - '0') * 10 + (s[18] - '0'));

  if ((month < 1) || (month > 12) || (day < 1) || (day > 31) || (hours >= 24)
      || (minutes >= 60) || (seconds >= 60))
    return false;

  std::int64_t nanoseconds(0);

  if (s[19] == '.')
    {
      int frac_digits = s.size() - 20 - 1;
      assert(frac_digits >= 0);
      const std::from_chars_result r =
          std::from_chars(s.begin() + 20, s.end() - 1, nanoseconds);

      if ((r.ec != std::errc{}) || (r.ptr != s.end() - 1))
        return false;

      for (; frac_digits != 9; ++frac_digits)
        nanoseconds *= 10;
    }

  t = std::chrono::sys_days(std::chrono::year_month_day(
          std::chrono::year(year), std::chrono::month(month),
          std::chrono::day(day)))
      + std::chrono::duration_cast<
          std::chrono::system_clock::time_point::duration>(
          (std::chrono::hours(hours) + std::chrono::minutes(minutes)
           + std::chrono::seconds(seconds)
           + std::chrono::nanoseconds(nanoseconds)));

  return true;
}
