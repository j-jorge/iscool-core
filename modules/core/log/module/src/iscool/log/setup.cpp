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
#include "iscool/log/setup.h"

#include "iscool/log/detail/get_message_dispatcher.h"
#include "iscool/log/detail/logger_thread.h"
#include "iscool/log/detail/message_dispatcher.h"

#ifndef NDEBUG
#include "iscool/error/synopsis.h"
#include "iscool/log/detail/print_to_console.h"
#include "iscool/log/nature/error.h"
#include "iscool/strings/format.h"
#endif

void iscool::log::initialize()
{
#ifndef NDEBUG
    message_delegates delegates;
    delegates.print_message = &detail::print_to_console;

    delegates.print_error =
        []( const context& context, const error::synopsis& synopsis ) -> void
        {
            detail::print_to_console
            ( nature::error(), context,
              iscool::strings::format
              ( "%1%-%2%: %3%", synopsis.get_category(), synopsis.get_code(),
                synopsis.get_message() ) );
        };
    
    detail::get_message_dispatcher().register_delegates( delegates );
#endif
}

void iscool::log::finalize()
{
    detail::stop_logger_thread();
    detail::get_message_dispatcher().clear();
}

