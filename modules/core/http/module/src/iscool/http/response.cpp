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
#include "iscool/http/response.h"

iscool::http::response::response( int code, const std::vector< char >& body )
    : _code( code ),
      _body( body )
{

}
            
int iscool::http::response::get_code() const
{
    return _code;
}

const std::vector< char >& iscool::http::response::get_body() const
{
    return _body;
}
