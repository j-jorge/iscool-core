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
#ifndef ISCOOL_HTTP_MOCKUP_H
#define ISCOOL_HTTP_MOCKUP_H

#include <iscool/optional.hpp>

#include <string>
#include <vector>

namespace iscool
{
  namespace http
  {
    class mockup
    {
    public:
      mockup();

      void set_enabled(bool enabled);
      bool is_enabled() const;

      void add_predefined_responses(const std::string& path);

      iscool::optional<std::vector<char>>
      get_predefined_response(const std::string& url) const;

    private:
      bool _enabled;
      std::vector<std::string> _responses;
    };
  }
}

#endif
