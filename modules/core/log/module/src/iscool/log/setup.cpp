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
#include <iscool/log/setup.hpp>

#include <iscool/log/detail/get_message_dispatcher.hpp>
#include <iscool/log/detail/logger_thread.hpp>
#include <iscool/log/detail/message_dispatcher.hpp>
#include <iscool/log/detail/print_to_console.hpp>

void iscool::log::initialize(const std::string_view& android_tag)
{
  iscool::log::detail::set_android_tag(android_tag);
}

void iscool::log::finalize()
{
  detail::stop_logger_thread();
  detail::get_message_dispatcher().clear();
}

iscool::log::scoped_initializer::scoped_initializer()
{
  initialize("IsCool");
}

iscool::log::scoped_initializer::scoped_initializer(
    const std::string_view& android_tag)
{
  initialize(android_tag);
}

iscool::log::scoped_initializer::~scoped_initializer()
{
  finalize();
}
