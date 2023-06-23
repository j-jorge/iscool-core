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
#include "iscool/http/request.h"

#include "gtest/gtest.h"

TEST(iscool_http_request, type)
{
  iscool::http::request request;
  request.set_type(iscool::http::request::type::get);
  EXPECT_EQ(iscool::http::request::type::get, request.get_type());

  request.set_type(iscool::http::request::type::post);
  EXPECT_EQ(iscool::http::request::type::post, request.get_type());
}

TEST(iscool_http_request, url)
{
  iscool::http::request request;
  request.set_url("http://example.com");
  EXPECT_EQ("http://example.com", request.get_url());
}

TEST(iscool_http_request, body)
{
  iscool::http::request request;
  request.set_body("abc");
  EXPECT_EQ("abc", request.get_body());
}

TEST(iscool_http_request, headers)
{
  iscool::http::request request;
  const std::vector<std::string> headers({ "abc", "def" });
  request.set_headers(headers);
  EXPECT_EQ(headers, request.get_headers());
}

TEST(iscool_http_request, response_handler)
{
  iscool::http::request request;
  bool called(false);

  request.set_response_handler(
      [&called](const iscool::http::response&) -> void
      {
        called = true;
      });

  request.get_response_handler()(
      iscool::http::response(200, std::vector<char>()));
  EXPECT_TRUE(called);
}
