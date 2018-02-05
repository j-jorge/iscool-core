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
#include "iscool/http/service_statistics.h"

#include "iscool/http/detail/get_service_statistics.h"
#include "iscool/http/detail/service_statistics.h"

void iscool::http::reset_service_quality()
{
    detail::get_service_statistics().reset();
}

float iscool::http::get_service_quality()
{
    return detail::get_service_statistics().get_last_measure();
}

iscool::signals::connection
iscool::http::connect_to_service_quality_changed
( const boost::function< void( float ) >& f )
{
    return detail::get_service_statistics().connect_to_quality_changed( f );
}

