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
#ifndef ISCOOL_META_COMBINE_OR_TESTS_H
#define ISCOOL_META_COMBINE_OR_TESTS_H

#include <type_traits>

namespace iscool
{
    namespace meta
    {
        namespace combine_or_tests
        {
            namespace single
            {
                typedef iscool::meta::combine_or< true > true_type;

                static_assert
                ( true_type::value,
                  "Incorrect value of combine_or< true >." );

                static_assert
                ( std::is_convertible
                  <
                      decltype( true_type::value ),
                      bool
                  >::value,
                  "combine_or< true >::value is not a boolean." );

                typedef iscool::meta::combine_or< false > false_type;
                
                static_assert
                ( !false_type::value,
                  "Incorrect value of combine_or< false >." );

                static_assert
                ( std::is_convertible
                  <
                      decltype( false_type::value ),
                      bool
                  >::value,
                  "combine_or< false >::value is not a boolean." );
            }

            namespace begins_with_true
            {
                typedef
                iscool::meta::combine_or< true, false, true, true, false >
                result_type;

                static_assert
                ( result_type::value,
                  "Incorrect value of combine_or<> beginning with true." );

                static_assert
                ( std::is_convertible
                  <
                      decltype( result_type::value ),
                      bool
                  >::value,
                  "combine_or<> beginning with true is not a boolean." );
            }

            namespace begins_with_false
            {
                typedef
                iscool::meta::combine_or< false, false, true, false, true >
                result_type;

                static_assert
                ( result_type::value,
                  "Incorrect value of combine_or<> beginning with false." );

                static_assert
                ( std::is_convertible
                  <
                      decltype( result_type::value ),
                      bool
                  >::value,
                  "combine_or<> beginning with false is not a boolean." );
            }

            namespace true_at_end
            {
                typedef
                iscool::meta::combine_or< false, false, false, false, true >
                result_type;

                static_assert
                ( result_type::value,
                  "Incorrect value of combine_or with a single true at end." );

                static_assert
                ( std::is_convertible
                  <
                      decltype( result_type::value ),
                      bool
                  >::value,
                  "combine_or<> with a single true at end is not a boolean." );
            }

            namespace true_at_start
            {
                typedef
                iscool::meta::combine_or< true, false, false, false, false >
                result_type;

                static_assert
                ( result_type::value,
                  "Incorrect value of combine_or with a single true at"
                  " start." );

                static_assert
                ( std::is_convertible
                  <
                      decltype( result_type::value ),
                      bool
                  >::value,
                  "combine_or<> with a single true at start is not a"
                  " boolean." );
            }
        }
    }
}

#endif
