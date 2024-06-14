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
#include <iscool/error/synopsis.hpp>
#include <iscool/log/log.hpp>
#include <iscool/log/message_delegates_registry.hpp>
#include <iscool/log/nature/nature.hpp>
#include <iscool/log/setup.hpp>
#include <iscool/optional.hpp>

#include <gtest/gtest.h>

class iscool_log_test : public ::testing::Test
{
public:
  iscool_log_test();
  ~iscool_log_test();

protected:
  iscool::log::nature::nature _nature;
  iscool::log::context _context;
  std::string _message;

  iscool::optional<iscool::error::synopsis> _error;

private:
  void print_message(const iscool::log::nature::nature& nature,
                     const iscool::log::context& context,
                     const std::string& message);

  void print_error(const iscool::log::context& context,
                   const iscool::error::synopsis& error);

private:
  std::size_t _delegates_id;
};

iscool_log_test::iscool_log_test()
{
  iscool::log::message_delegates delegates;
  delegates.print_message =
      std::bind(&iscool_log_test::print_message, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3);
  delegates.print_error =
      std::bind(&iscool_log_test::print_error, this, std::placeholders::_1,
                std::placeholders::_2);

  iscool::log::initialize();
  _delegates_id = iscool::log::register_delegates(delegates);
}

iscool_log_test::~iscool_log_test()
{
  iscool::log::unregister_delegates(_delegates_id);
  iscool::log::finalize();
}

void iscool_log_test::print_message(const iscool::log::nature::nature& nature,
                                    const iscool::log::context& context,
                                    const std::string& message)
{
  _nature = nature;
  _context = context;
  _message = message;
}

void iscool_log_test::print_error(const iscool::log::context& context,
                                  const iscool::error::synopsis& error)
{
  _context = context;
  _error = error;
}

TEST_F(iscool_log_test, log)
{
  const iscool::log::nature::nature nature("nature");

  const std::size_t line(__LINE__);
  ic_log(nature, "reporter", "message %1%: %2%", 24, 42);

  EXPECT_EQ(nature, _nature);
  EXPECT_EQ("reporter", _context.get_reporter());
  EXPECT_EQ(__FILE__, _context.get_file());
  EXPECT_EQ(line + 1, _context.get_line());
  EXPECT_EQ("message 24: 42", _message);

  EXPECT_FALSE(!!_error);
}
