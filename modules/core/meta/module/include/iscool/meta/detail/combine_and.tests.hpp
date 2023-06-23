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
#ifndef ISCOOL_META_COMBINE_AND_TESTS_H
#define ISCOOL_META_COMBINE_AND_TESTS_H

#include <type_traits>

namespace iscool
{
  namespace meta
  {
    namespace combien_and_tests
    {
      namespace single
      {
        typedef iscool::meta::combine_and<true> true_type;

        static_assert(true_type::value,
                      "Incorrect value of combine_and< true >.");

        static_assert(
            std::is_convertible<decltype(true_type::value), bool>::value,
            "combine_and< true >::value is not a boolean.");

        typedef iscool::meta::combine_and<false> false_type;

        static_assert(!false_type::value,
                      "Incorrect value of combine_and< false >.");

        static_assert(
            std::is_convertible<decltype(false_type::value), bool>::value,
            "combine_and< false >::value is not a boolean.");
      }

      namespace begins_with_true
      {
        typedef iscool::meta::combine_and<true, false, true, true, false>
            result_type;

        static_assert(!result_type::value,
                      "Incorrect value of combine_and<> beginning with true.");

        static_assert(
            std::is_convertible<decltype(result_type::value), bool>::value,
            "combine_and<> beginning with true is not a boolean.");
      }

      namespace begins_with_false
      {
        typedef iscool::meta::combine_and<false, false, true, false, true>
            result_type;

        static_assert(
            !result_type::value,
            "Incorrect value of combine_and<> beginning with false.");

        static_assert(
            std::is_convertible<decltype(result_type::value), bool>::value,
            "combine_and<> beginning with false is not a boolean.");
      }

      namespace multi_all_true
      {
        typedef iscool::meta::combine_and<true, true, true, true, true>
            result_type;

        static_assert(result_type::value,
                      "Incorrect value of combine_and with only trues.");

        static_assert(
            std::is_convertible<decltype(result_type::value), bool>::value,
            "combine_and<> with only trues is not a boolean.");
      }

      namespace false_at_end
      {
        typedef iscool::meta::combine_and<true, true, true, true, false>
            result_type;

        static_assert(!result_type::value,
                      "Incorrect value of combine_and with a single false at"
                      " end.");

        static_assert(
            std::is_convertible<decltype(result_type::value), bool>::value,
            "combine_and<> with a single false at end is not a"
            " boolean.");
      }

      namespace false_at_start
      {
        typedef iscool::meta::combine_and<false, true, true, true, true>
            result_type;

        static_assert(!result_type::value,
                      "Incorrect value of combine_and with a single false at"
                      " start.");

        static_assert(
            std::is_convertible<decltype(result_type::value), bool>::value,
            "combine_and<> with a single false at start is not a"
            " boolean.");
      }
    }
  }
}

#endif
