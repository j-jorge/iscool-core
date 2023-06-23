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
#ifndef ISCOOL_RESOURCES_RESOLVER_H
#define ISCOOL_RESOURCES_RESOLVER_H

#include <string>

namespace iscool
{
  namespace resources
  {
    class resolver
    {
    public:
      resolver(const std::string& search_path, const std::string& extension);

      std::string get_file_path(const std::string& name) const;

    private:
      const std::string _search_path;
      const std::string _extension;
    };
  }
}

#endif
