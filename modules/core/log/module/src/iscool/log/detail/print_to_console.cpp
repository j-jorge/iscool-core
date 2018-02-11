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
#include "iscool/log/detail/print_to_console.h"

#include "iscool/log/context.h"
#include "iscool/log/nature/nature.h"

#if defined __APPLE__
#include "TargetConditionals.h"
#endif

#if defined __ANDROID__

#include "iscool/log/nature/debug.h"
#include "iscool/log/nature/error.h"
#include "iscool/log/nature/info.h"
#include "iscool/log/nature/warning.h"

#include <android/log.h>

void iscool::log::detail::print_to_console
( const nature::nature& nature, const context& context,
  const std::string& message )
{
    android_LogPriority priority( ANDROID_LOG_VERBOSE );

    if ( nature == iscool::log::nature::error() )
        priority = ANDROID_LOG_ERROR;
    else if ( nature == iscool::log::nature::warning() )
        priority = ANDROID_LOG_WARN;
    else if ( nature == iscool::log::nature::info() )
        priority = ANDROID_LOG_INFO;
    else if ( nature == iscool::log::nature::debug() )
        priority = ANDROID_LOG_DEBUG;

    const std::string& reporter( context.get_reporter() );
    const std::string& origin( context.get_origin() );
                       
    __android_log_print
        ( priority, "IsCool", "[%s][%s] %s:%d",
          reporter.c_str(), origin.c_str(), context.get_file().c_str(),
          (unsigned int)context.get_line() );
    __android_log_print
        ( priority, "IsCool", "[%s][%s] %s",
          reporter.c_str(), origin.c_str(), message.c_str() );
}

#elif ( TARGET_OS_IPHONE == 1 )

#include <asl.h>
#include <unistd.h>

void iscool::log::detail::print_to_console
( const nature::nature& nature, const context& context,
  const std::string& message )
{
    const std::string& reporter( context.get_reporter() );
    const std::string& origin( context.get_origin() );

    asl_add_log_file(NULL, STDERR_FILENO);
    asl_log
        ( nullptr, nullptr, ASL_LEVEL_INFO, "[%s][%s][%s] %s:%d",
          nature.string().c_str(), reporter.c_str(), origin.c_str(),
          context.get_file().c_str(), (unsigned int)context.get_line() );
    asl_log
        ( nullptr, nullptr, ASL_LEVEL_INFO, "[%s][%s][%s] %s",
          nature.string().c_str(), reporter.c_str(), origin.c_str(),
          message.c_str() );
}

#elif ISCOOL_LOG_PRETTY_PRINT != 0

#include "iscool/log/detail/prettify.h"

#include <iostream>

void iscool::log::detail::print_to_console
( const nature::nature& nature, const context& context,
  const std::string& message )
{
    std::clog
        << prettify
        ( "[" + nature.string() + "][" + context.get_reporter() + "]["
          + context.get_origin() + "] " + message )
        << '\n';
}

#else

#include <iostream>

void iscool::log::detail::print_to_console
( const nature::nature& nature, const context& context,
  const std::string& message )
{
    std::clog << '[' << nature.string() << "][" << context.get_reporter()
              << "][" << context.get_origin() << "] " << message << '\n';
}

#endif
