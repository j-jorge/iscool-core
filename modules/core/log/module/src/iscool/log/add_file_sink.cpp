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
#include <iscool/log/add_file_sink.hpp>

#include <iscool/log/context.hpp>
#include <iscool/log/detail/get_message_dispatcher.hpp>
#include <iscool/log/detail/logger_thread.hpp>
#include <iscool/log/detail/message_dispatcher.hpp>
#include <iscool/log/nature/error.hpp>
#include <iscool/log/nature/nature.hpp>

#include <iscool/error/synopsis.hpp>

#include <format>
#include <fstream>
#include <iomanip>
#include <memory>

void iscool::log::add_file_sink(const std::string& path)
{
  add_file_sink(path, std::ios_base::out | std::ios_base::trunc);
}

void iscool::log::add_file_sink(const std::string& path,
                                std::ios_base::openmode mode)
{
  std::shared_ptr<std::ofstream> log_file(
      std::make_shared<std::ofstream>(path, mode));

  const auto write_log(
      [log_file](const iscool::log::nature::nature& nature,
                 const context& context, const std::string& message)
      {
        detail::queue_in_logger_thread(
            [=]() -> void
            {
              const std::time_t t = std::time(nullptr);
              *log_file << '[' << std::put_time(std::gmtime(&t), "%F %T")
                        << "][" << nature.string() << "]["
                        << context.get_reporter() << "] " << message
                        << std::endl;
            });
      });

  message_delegates delegates;
  delegates.print_message = write_log;

  delegates.print_error = [write_log](const context& context,
                                      const error::synopsis& synopsis) -> void
  {
    write_log(nature::error(), context,
              std::format("{}-{}: {}", synopsis.get_category(),
                          synopsis.get_code(), synopsis.get_message()));
  };

  detail::get_message_dispatcher().register_delegates(delegates);
}
