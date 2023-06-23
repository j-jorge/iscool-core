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
#ifndef ISCOOL_PREFERENCES_DETAIL_PROPERTY_IMPL_TPP
#define ISCOOL_PREFERENCES_DETAIL_PROPERTY_IMPL_TPP

template <typename T>
iscool::preferences::detail::property<T>::property() = default;

template <typename T>
iscool::preferences::detail::property<T>::property(std::string&& name,
                                                   T&& fallback)
  : name(std::forward<std::string>(name))
  , fallback(std::forward<T>(fallback))
{}

template <typename T>
iscool::preferences::detail::property<T>::property(std::string&& name,
                                                   const T& fallback)
  : name(std::forward<std::string>(name))
  , fallback(fallback)
{}

#endif
