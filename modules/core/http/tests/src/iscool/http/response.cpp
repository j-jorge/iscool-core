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
#include <iscool/http/response.hpp>

#include "gtest/gtest.h"

TEST(iscool_http_request, constructor)
{
  const std::vector<char> body({ 'a', 'c', 'd' });
  iscool::http::response response(24, body);

  EXPECT_EQ(24, response.get_code());
  EXPECT_EQ(body, response.get_body());
}
