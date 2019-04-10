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
#ifndef ISCOOL_PREFERENCES_DETAIL_GLOBAL_PROPERTIES_H
#define ISCOOL_PREFERENCES_DETAIL_GLOBAL_PROPERTIES_H

#include <unordered_map>
#include <string>

namespace iscool
{
    namespace preferences
    {
        namespace detail
        {
            const std::unordered_map< std::string, std::string >&
            get_global_properties();
            
            void set_global_properties
            ( const std::unordered_map< std::string, std::string >&
              properties );
            
            int get_global_properties_version();
        }
    }
}

#endif
