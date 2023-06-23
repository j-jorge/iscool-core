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
#ifndef ISCOOL_STRINGS_FORMAT_TPP
#define ISCOOL_STRINGS_FORMAT_TPP

#include <iscool/strings/detail/formatter_bridge.hpp>

template <typename... Args>
std::string iscool::strings::format(const char* pattern, Args... args)
{
  detail::formatter* formatter(detail::create_formatter(pattern));

  try
    {
      (detail::append_to_formatter<Args>(*formatter, args), ...);
    }
  catch (...)
    {
      detail::release_formatter(formatter);
      throw;
    }

  const std::string result(detail::get_formatter_string(*formatter));
  detail::release_formatter(formatter);

  return result;
}

#endif
