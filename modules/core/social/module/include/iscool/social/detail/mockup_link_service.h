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
#ifndef ISCOOL_SOCIAL_DETAIL_MOCKUP_LINK_SERVICE_H
#define ISCOOL_SOCIAL_DETAIL_MOCKUP_LINK_SERVICE_H

#include <string>

namespace iscool
{
    namespace social
    {
        namespace detail
        {
            class mockup_link_service
            {
            public:
                void open_in_facebook( const std::string& path );
                void open_in_twitter( const std::string& path );

            };
        }
    }
}

#endif
