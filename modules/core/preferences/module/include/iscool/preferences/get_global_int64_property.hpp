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
#ifndef ISCOOL_PREFERENCES_GET_GLOBAL_INT64_PROPERTY_H
#define ISCOOL_PREFERENCES_GET_GLOBAL_INT64_PROPERTY_H

#include <iscool/preferences/int64_property.hpp>

namespace iscool
{
  namespace preferences
  {
    std::int64_t get_global_int64_property(const int64_property& property);
  }
}

#endif
