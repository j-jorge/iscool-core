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
#include "iscool/log/add_file_sink.h"

#include "iscool/log/context.h"
#include "iscool/log/detail/get_message_dispatcher.h"
#include "iscool/log/detail/logger_thread.h"
#include "iscool/log/detail/message_dispatcher.h"
#include "iscool/log/nature/error.h"
#include "iscool/log/nature/nature.h"

#include "iscool/error/synopsis.h"
#include "iscool/strings/format.h"

#include <fstream>
#include <memory>

void iscool::log::add_file_sink(const std::string& path)
{
  std::shared_ptr<std::ofstream> log_file(std::make_shared<std::ofstream>(
      path, std::ios_base::out | std::ios_base::trunc));

  const auto write_log(
      [log_file](const iscool::log::nature::nature& nature,
                 const context& context, const std::string& message)
      {
        detail::queue_in_logger_thread(
            [=]() -> void
            {
              *log_file << '[' << nature.string() << "]["
                        << context.get_reporter() << "]["
                        << context.get_origin() << "] " << message
                        << std::endl;
            });
      });

  message_delegates delegates;
  delegates.print_message = write_log;

  delegates.print_error = [write_log](const context& context,
                                      const error::synopsis& synopsis) -> void
  {
    write_log(nature::error(), context,
              iscool::strings::format("%1%-%2%: %3%", synopsis.get_category(),
                                      synopsis.get_code(),
                                      synopsis.get_message()));
  };

  detail::get_message_dispatcher().register_delegates(delegates);
}
