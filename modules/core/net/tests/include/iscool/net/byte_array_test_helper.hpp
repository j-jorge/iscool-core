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
#ifndef ISCOOL_NET_TESTS_BYTE_ARRAY_TEST_HELPER_H
#define ISCOOL_NET_TESTS_BYTE_ARRAY_TEST_HELPER_H

#include <iscool/net/byte_array.hpp>
#include <string>

namespace iscool
{
  namespace net
  {
    namespace tests
    {
      byte_array std_string_to_byte_array(const std::string& string);

      void expect_eq(const byte_array& first, const byte_array& second);
    }
  }
}

#endif
