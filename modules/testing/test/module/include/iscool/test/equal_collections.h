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
#ifndef ISCOOL_TEST_EQUAL_COLLECTIONS_H
#define ISCOOL_TEST_EQUAL_COLLECTIONS_H

#include <string>

namespace iscool
{
    namespace test
    {
        template< typename LeftContainer, typename RightContainer >
        void assert_equal_collections
        ( LeftContainer left, RightContainer right,
          const std::string& message = std::string() );
    }
}

#include "iscool/test/detail/equal_collections.tpp"

#endif
