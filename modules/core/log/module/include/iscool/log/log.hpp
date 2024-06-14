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
#ifndef ISCOOL_LOG_H
#define ISCOOL_LOG_H

#include <iscool/log/context.hpp>
#include <iscool/log/detail/get_message_dispatcher.hpp>
#include <iscool/log/detail/message_dispatcher.hpp>
#include <iscool/log/detail/message_dispatcher.impl.tpp>

#define ic_log(nature, reporter, ...)                                         \
  ::iscool::log::detail::get_message_dispatcher().dispatch(                   \
      nature, ::iscool::log::context(reporter, __FILE__, __LINE__),           \
      __VA_ARGS__)

#endif
