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
#include <iscool/preferences/detail/global_properties.hpp>

namespace iscool
{
  namespace preferences
  {
    namespace detail
    {
      static std::unordered_map<std::string, std::string> global_properties;
      static int global_properties_version(0);
    }
  }
}

const std::unordered_map<std::string, std::string>&
iscool::preferences::detail::get_global_properties()
{
  return global_properties;
}

void iscool::preferences::detail::set_global_properties(
    const std::unordered_map<std::string, std::string>& properties)
{
  global_properties = properties;
  ++global_properties_version;
}

int iscool::preferences::detail::get_global_properties_version()
{
  return global_properties_version;
}
