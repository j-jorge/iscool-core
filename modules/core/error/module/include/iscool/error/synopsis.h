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
#ifndef ISCOOL_ERROR_SYNOPSIS_H
#define ISCOOL_ERROR_SYNOPSIS_H

#include <string>

namespace iscool
{
    namespace error
    {
        class synopsis
        {
        public:
            synopsis
            ( std::size_t code, const std::string& category,
              const std::string& title, const std::string& message );
            
            std::size_t get_code() const;
            const std::string& get_category() const;
            const std::string& get_title() const;
            const std::string& get_message() const;

        private:
            std::size_t m_code;
            std::string m_category;
            std::string m_title;
            std::string m_message;
        };
    }
}

#endif

