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
#ifndef ISCOOL_PREFERENCES_DETAIL_GET_GLOBAL_PROPERTY_TPP
#define ISCOOL_PREFERENCES_DETAIL_GET_GLOBAL_PROPERTY_TPP

#include "iscool/preferences/detail/global_properties.h"

#include "iscool/preferences/property_map.impl.h"

template< typename T >
T iscool::preferences::detail::get_global_property
( const property< T >& property )
{
    const iscool::optional< T > result
        ( detail::global_properties().get< T >( property.name ) );

    if ( result )
        return *result;

    return property.fallback;
}

#endif
