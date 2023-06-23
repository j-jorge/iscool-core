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
#ifndef ISCOOL_STRINGS_VECTOR_TO_STRING_TPP
#define ISCOOL_STRINGS_VECTOR_TO_STRING_TPP

#include <sstream>

template <typename T>
std::string iscool::strings::vector_to_string(const std::vector<T>& v,
                                              char separator)
{
  if (v.empty())
    return "";

  std::ostringstream oss;

  typename std::vector<T>::const_iterator it(v.begin());
  typename std::vector<T>::const_iterator eit(v.end());

  oss << *it;

  for (++it; it != eit; ++it)
    oss << separator << *it;

  return oss.str();
}

#endif
