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
#ifndef ISCOOL_STRINGS_DETAIL_FORMATTER_BRIDGE_H
#define ISCOOL_STRINGS_DETAIL_FORMATTER_BRIDGE_H

#include <string>

namespace iscool
{
  namespace strings
  {
    namespace detail
    {
      class formatter;

      formatter* create_formatter(const std::string& pattern);
      void release_formatter(formatter* f);

      std::string get_formatter_string(const formatter& f);

      template <typename T>
      int append_to_formatter(formatter& f, T value);

      extern template int append_to_formatter<const char*>(formatter& f,
                                                           const char* value);
      extern template int
      append_to_formatter<const std::string&>(formatter& f,
                                              const std::string& value);
      extern template int append_to_formatter<std::string>(formatter& f,
                                                           std::string value);
      extern template int append_to_formatter<short>(formatter& f,
                                                     short value);
      extern template int
      append_to_formatter<unsigned short>(formatter& f, unsigned short value);
      extern template int append_to_formatter<int>(formatter& f, int value);
      extern template int
      append_to_formatter<unsigned int>(formatter& f, unsigned int value);
      extern template int append_to_formatter<long>(formatter& f, long value);
      extern template int
      append_to_formatter<unsigned long>(formatter& f, unsigned long value);
      extern template int append_to_formatter<long long>(formatter& f,
                                                         long long value);
      extern template int
      append_to_formatter<unsigned long long>(formatter& f,
                                              unsigned long long value);
      extern template int append_to_formatter<float>(formatter& f,
                                                     float value);
      extern template int append_to_formatter<double>(formatter& f,
                                                      double value);
    }
  }
}

#endif
