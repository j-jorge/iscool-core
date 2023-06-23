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
#include <iscool/http/compose_url.hpp>

#include <gtest/gtest.h>

TEST(iscool_http_compose_url, no_arguments)
{
  EXPECT_EQ("example.com", iscool::http::compose_url("example.com", {}));
}

TEST(iscool_http_compose_url, single_argument)
{
  EXPECT_EQ(
      "example.com?arg1=value1",
      iscool::http::compose_url("example.com", { { "arg1", "value1" } }));
}

TEST(iscool_http_compose_url, two_arguments)
{
  EXPECT_EQ(
      "example.com?arg1=value1&arg2=value2",
      iscool::http::compose_url(
          "example.com", { { "arg1", "value1" }, { "arg2", "value2" } }));
}

TEST(iscool_http_compose_url, multiple_arguments)
{
  EXPECT_EQ(
      "example.com?arg1=value1&arg2=value2&arg3=value3",
      iscool::http::compose_url("example.com", { { "arg1", "value1" },
                                                 { "arg2", "value2" },
                                                 { "arg3", "value3" } }));
}

TEST(iscool_http_compose_url, escape_values)
{
  EXPECT_EQ("example.com?arg1=ftp%3A%2F%2Fa%20b&arg2=c%2B%26%3Fd",
            iscool::http::compose_url("example.com", { { "arg1", "ftp://a b" },
                                                       { "arg2", "c+&?d" } }));
}
