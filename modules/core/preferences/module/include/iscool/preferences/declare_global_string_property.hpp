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
#ifndef ISCOOL_PREFERENCES_DECLARE_GLOBAL_STRING_PROPERTY_H
#define ISCOOL_PREFERENCES_DECLARE_GLOBAL_STRING_PROPERTY_H

#include <iscool/preferences/string_property.hpp>

namespace iscool
{
  namespace preferences
  {
    string_property declare_global_string_property(std::string&& name,
                                                   std::string&& fallback);
  }
}

#endif
