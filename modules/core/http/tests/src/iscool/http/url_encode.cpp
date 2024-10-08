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
#include <iscool/http/url_encode.hpp>

#include <gtest/gtest.h>

TEST(iscool_http, url_encode)
{
  EXPECT_EQ("ftp%3A%2F%2Fa%20b", iscool::http::url_encode("ftp://a b"));
  EXPECT_EQ("c%2B%26%3Fd", iscool::http::url_encode("c+&?d"));
}
