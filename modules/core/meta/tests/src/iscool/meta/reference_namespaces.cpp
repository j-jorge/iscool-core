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
#include <iscool/meta/reference_namespaces.hpp>

#include <gtest/gtest.h>

typedef int in_global_namespace;

namespace iscool
{
  namespace meta
  {
    namespace test
    {
      typedef std::string in_namespace;
    }
  }
}

TEST(iscool_meta_reference_namespaces, global_namespace)
{
  const bool same(
      std::is_same<int, ic_reference_namespaces() in_global_namespace>::value);

  EXPECT_TRUE(same);
}

TEST(iscool_meta_reference_namespaces, non_global_namespace)
{
  const bool same(
      std::is_same<std::string, ic_reference_namespaces((iscool)(meta)(test))
                                    in_namespace>::value);

  EXPECT_TRUE(same);
}
