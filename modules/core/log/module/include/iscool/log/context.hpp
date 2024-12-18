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
#pragma once

#include <string>

namespace iscool
{
  namespace log
  {
    class context
    {
    public:
      context();
      context(std::string reporter, std::string file, std::size_t line);
      ~context();

      const std::string& get_reporter() const;
      const std::string& get_file() const;
      std::size_t get_line() const;

    private:
      friend bool operator==(const context& lhs, const context& rhs)
      {
        return (lhs._line == rhs._line) && (lhs._reporter == rhs._reporter)
               && (lhs._file == rhs._file);
      }

      friend bool operator!=(const context& lhs, const context& rhs)
      {
        return !(lhs == rhs);
      }

    private:
      std::string _reporter;
      std::string _file;
      std::size_t _line;
    };
  }
}
