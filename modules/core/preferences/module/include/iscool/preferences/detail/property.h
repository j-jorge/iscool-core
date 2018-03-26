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
#ifndef ISCOOL_PREFERENCES_DETAIL_PROPERTY_H
#define ISCOOL_PREFERENCES_DETAIL_PROPERTY_H

#include <string>

namespace iscool
{
    namespace preferences
    {
        namespace detail
        {
            template< typename T >
            class property
            {
            public:
                property();
                property( std::string&& name, T&& fallback );
                property( std::string&& name, const T& fallback );

            public:
                std::string name;
                T fallback;
            };

            extern template class property< bool >;
            extern template class property< float >;
            extern template class property< int >;
            extern template class property< std::string >;
        }
    }
}

#endif
