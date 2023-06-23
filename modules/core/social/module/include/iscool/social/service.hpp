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
#ifndef ISCOOL_SOCIAL_SERVICE_H
#define ISCOOL_SOCIAL_SERVICE_H

#include <iscool/social/link_service.hpp>
#include <iscool/social/share_service.hpp>

namespace iscool
{
  namespace social
  {
    class service
    {
    public:
      void share_message(const std::string& message);
      void share_file(const std::string& file_path,
                      const std::string& message);

      void open_in_facebook(const std::string& page);
      void open_in_twitter(const std::string& page);

    private:
      share_service _share;
      link_service _link;
    };
  }
}

#endif
