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
#ifndef ISCOOL_LOG_CONTEXT_H
#define ISCOOL_LOG_CONTEXT_H

#include <string>

namespace iscool
{
    namespace log
    {
        class context
        {
        public:
            context();
            context
            ( const std::string& reporter, const std::string origin,
              const std::string& file, std::size_t line );

            const std::string& get_reporter() const;
            const std::string& get_origin() const;
            const std::string& get_file() const;
            std::size_t get_line() const;

        private:
            std::string _reporter;
            std::string _origin;
            std::string _file;
            std::size_t _line;
        };
    }
}

#endif
