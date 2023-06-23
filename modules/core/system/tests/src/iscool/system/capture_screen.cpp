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
#include "iscool/system/capture_screen.h"
#include "iscool/system/setup.h"

#include "iscool/test/debug_crash.h"

#include <gtest/gtest.h>

TEST(iscool_system_test, capture_screen)
{
  std::function<void(std::string)> captured_callback;
  std::string captured_file_name;

  const auto capture_screen(
      [&](const std::string& file_name,
          std::function<void(std::string)> on_capture) -> void
      {
        captured_file_name = file_name;
        captured_callback = on_capture;
      });

  iscool::system::initialize(capture_screen);

  std::string captured_full_path;

  const auto callback(
      [&captured_full_path](std::string full_path) -> void
      {
        captured_full_path = full_path;
      });

  iscool::signals::connection connection(
      iscool::system::capture_screen("test", callback));

  EXPECT_TRUE(connection.connected());
  EXPECT_EQ("test", captured_file_name);

  captured_callback("full/path");

  EXPECT_EQ("full/path", captured_full_path);

  iscool::system::finalize();
}

TEST(iscool_system_test, capture_screen_disconnected)
{
  std::function<void(std::string)> captured_callback;

  const auto capture_screen(
      [&](const std::string& file_name,
          std::function<void(std::string)> on_capture) -> void
      {
        captured_callback = on_capture;
      });

  iscool::system::initialize(capture_screen);

  bool called(false);

  const auto callback(
      [&called](std::string full_path) -> void
      {
        called = true;
      });

  iscool::signals::connection connection(
      iscool::system::capture_screen("test", callback));
  connection.disconnect();

  captured_callback("full/path");

  EXPECT_FALSE(called);

  iscool::system::finalize();
}

TEST(iscool_system_test, capture_screen_in_capture)
{
  std::vector<std::function<void(std::string)>> captured_callback;

  const auto capture_screen(
      [&](const std::string& file_name,
          std::function<void(std::string)> on_capture) -> void
      {
        captured_callback.push_back(on_capture);
      });

  iscool::system::initialize(capture_screen);

  std::string second_capture_full_path;
  const auto second_capture(
      [&second_capture_full_path](std::string full_path) -> void
      {
        second_capture_full_path = full_path;
      });
  const auto callback(
      [second_capture](std::string full_path) -> void
      {
        iscool::system::capture_screen("test2", second_capture);
      });

  iscool::system::capture_screen("test", callback);

  captured_callback.front()("");
  captured_callback.back()("second/full/path");

  EXPECT_EQ("second/full/path", second_capture_full_path);

  iscool::system::finalize();
}

TEST(iscool_system_test, capture_immediate_call)
{
  const auto capture_screen(
      [](const std::string& file_name,
         std::function<void(std::string)> on_capture) -> void
      {
        on_capture("now");
      });

  iscool::system::initialize(capture_screen);

  bool called(false);

  const auto callback(
      [&called](std::string) -> void
      {
        called = true;
      });

  EXPECT_DEBUG_CRASH(iscool::system::capture_screen("test", callback));

  iscool::system::finalize();
}
