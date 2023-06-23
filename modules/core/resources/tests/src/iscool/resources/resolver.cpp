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
#include "iscool/resources/resolver.h"

#include <gtest/gtest.h>

TEST(iscool_resources_resolver, get_file_path)
{
  {
    const iscool::resources::resolver resolver("path/", ".ext");

    EXPECT_EQ("path/abc.ext", resolver.get_file_path("abc"));
    EXPECT_EQ("path/ABC.ext", resolver.get_file_path("ABC"));
  }

  {
    const iscool::resources::resolver resolver("some/path/", ".tmp");

    EXPECT_EQ("some/path/123456.tmp", resolver.get_file_path("123456"));
    EXPECT_EQ("some/path/987654.tmp", resolver.get_file_path("987654"));
  }
}
