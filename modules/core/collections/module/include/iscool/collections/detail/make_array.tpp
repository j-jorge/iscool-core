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
#ifndef ISCOOL_COLLECTIONS_MAKE_ARRAY_TPP
#define ISCOOL_COLLECTIONS_MAKE_ARRAY_TPP

template <typename T, typename... Arg>
std::array<T, sizeof...(Arg) + 1> iscool::collections::make_array(T head,
                                                                  Arg... arg)
{
  return std::array<T, sizeof...(Arg) + 1>{ { std::forward<T>(head),
                                              std::forward<Arg>(arg)... } };
}

#endif
