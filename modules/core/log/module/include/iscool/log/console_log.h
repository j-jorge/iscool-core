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
#ifndef ISCOOL_CONSOLE_LOG_H
#define ISCOOL_CONSOLE_LOG_H

#ifndef NDEBUG

  #include "iscool/log/context.h"
  #include "iscool/log/detail/print_to_console.h"
  #include "iscool/log/nature/debug.h"
  #include "iscool/strings/format.h"

  #define ic_console_log(reporter, ...)                                       \
    ::iscool::log::detail::print_to_console(                                  \
        ::iscool::log::nature::debug(),                                       \
        ::iscool::log::context(reporter, "Unknown", __FILE__, __LINE__),      \
        ::iscool::strings::format(__VA_ARGS__))

#else

  #define ic_console_log(context, ...)                                        \
    do                                                                        \
      {}                                                                      \
    while (0);

#endif

#endif
