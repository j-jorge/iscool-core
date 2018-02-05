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
#include "iscool/http/detail/request_handler.h"

#include "iscool/http/response.h"
#include "iscool/signals/implement_signal.h"

IMPLEMENT_SIGNAL( iscool::http::detail::request_handler, result, _on_result );
IMPLEMENT_SIGNAL( iscool::http::detail::request_handler, error, _on_error );

iscool::http::detail::request_handler::request_handler() = default;
iscool::http::detail::request_handler::~request_handler() = default;

void
iscool::http::detail::request_handler::process_response( const response& r )
{
    const std::vector<char> body( r.get_body() );

    if ( r.get_code() == 200 )
        _on_result( body );
    else
        _on_error( body );
}

void iscool::http::detail::request_handler::clear()
{
    _on_result.disconnect_all_slots();
    _on_error.disconnect_all_slots();
}
