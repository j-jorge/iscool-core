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
#include <iscool/http/request.hpp>

void iscool::http::request::set_type(type t)
{
  _type = t;
}

iscool::http::request::type iscool::http::request::get_type() const
{
  return _type;
}

void iscool::http::request::set_url(const std::string& url)
{
  _url = url;
}

const std::string& iscool::http::request::get_url() const
{
  return _url;
}

void iscool::http::request::set_body(const std::string& body)
{
  _body = body;
}

const std::string& iscool::http::request::get_body() const
{
  return _body;
}

void iscool::http::request::set_headers(
    const std::vector<std::string>& headers)
{
  _headers = headers;
}

const std::vector<std::string>& iscool::http::request::get_headers() const
{
  return _headers;
}

void iscool::http::request::set_response_handler(response_handler handler)
{
  assert(handler);
  _response_handler = std::move(handler);
}

iscool::http::request::response_handler
iscool::http::request::get_response_handler() const
{
  return _response_handler;
}
