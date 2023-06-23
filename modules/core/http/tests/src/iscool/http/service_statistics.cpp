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
#include "iscool/http/service_statistics.h"
#include "iscool/http/request.h"
#include "iscool/http/send.h"
#include "iscool/http/setup.h"
#include "iscool/optional.h"

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

class iscool_http_service_statistics_test : public ::testing::Test
{
public:
  iscool_http_service_statistics_test();
  ~iscool_http_service_statistics_test();

  void get();

  void dispatch_response(int code);

public:
  std::vector<iscool::http::request> _requests;
};

iscool_http_service_statistics_test::iscool_http_service_statistics_test()
{
  auto request_handler(
      [this](const iscool::http::request& request) -> void
      {
        _requests.push_back(request);
      });

  iscool::http::initialize(request_handler);
}

iscool_http_service_statistics_test::~iscool_http_service_statistics_test()
{
  iscool::http::finalize();
}

void iscool_http_service_statistics_test::get()
{
  auto on_result(
      [](std::vector<char> result) -> void
      {
      });
  auto on_error(
      [](std::vector<char> error) -> void
      {
      });

  iscool::http::get("http://www.example.org/", on_result, on_error);
}

void iscool_http_service_statistics_test::dispatch_response(int code)
{
  assert(!_requests.empty());

  const iscool::http::request request(_requests.front());
  _requests.erase(_requests.begin());

  assert(_requests.empty());

  request.get_response_handler()(iscool::http::response(code, {}));
}

TEST_F(iscool_http_service_statistics_test, initial_quality)
{
  EXPECT_FLOAT_EQ(1, iscool::http::get_service_quality());
}

TEST_F(iscool_http_service_statistics_test, to_zero_then_to_one)
{
  float last_quality(iscool::http::get_service_quality());

  while (last_quality != 0)
    {
      get();
      dispatch_response(404);

      const float quality(iscool::http::get_service_quality());
      ASSERT_PRED_FORMAT2(::testing::FloatLE, quality, last_quality);
      last_quality = quality;
    }

  get();
  dispatch_response(404);
  EXPECT_FLOAT_EQ(0, iscool::http::get_service_quality());

  while (last_quality != 1)
    {
      get();
      dispatch_response(200);

      const float quality(iscool::http::get_service_quality());
      ASSERT_PRED_FORMAT2(::testing::FloatLE, last_quality, quality);
      last_quality = quality;
    }

  get();
  dispatch_response(200);
  EXPECT_FLOAT_EQ(1, iscool::http::get_service_quality());
}

TEST_F(iscool_http_service_statistics_test, dispatch_changes)
{
  std::size_t calls(0);

  auto change(
      [&calls](float q) -> void
      {
        ++calls;
      });

  const iscool::signals::scoped_connection connection(
      iscool::http::connect_to_service_quality_changed(change));

  get();
  dispatch_response(200);

  EXPECT_EQ(std::size_t(0), calls);

  get();
  dispatch_response(400);
  EXPECT_EQ(std::size_t(1), calls);

  get();
  dispatch_response(200);
  EXPECT_EQ(std::size_t(1), calls);

  get();
  dispatch_response(400);
  EXPECT_EQ(std::size_t(2), calls);
}

TEST_F(iscool_http_service_statistics_test, reset)
{
  get();
  dispatch_response(404);

  EXPECT_PRED_FORMAT2(::testing::FloatLE, iscool::http::get_service_quality(),
                      1);

  get();
  iscool::http::reset_service_quality();
  EXPECT_FLOAT_EQ(1, iscool::http::get_service_quality());

  dispatch_response(404);
  EXPECT_FLOAT_EQ(1, iscool::http::get_service_quality());

  get();
  dispatch_response(404);

  EXPECT_PRED_FORMAT2(::testing::FloatLE, iscool::http::get_service_quality(),
                      1);
}
