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
#include "iscool/preferences/destroy_global_bool_property.h"

#include "iscool/preferences/detail/erase_global_property.h"
#include "iscool/preferences/detail/global_deserializer.h"

#include "iscool/preferences/property_deserializer.h"

void iscool::preferences::destroy_global_bool_property
( const bool_property& property )
{
    detail::global_deserializer().remove_bool_property( property.name );
    detail::erase_global_property( property );
}

