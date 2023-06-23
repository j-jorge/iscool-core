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
#ifndef ISCOOL_HTTP_HEQUEST_H
#define ISCOOL_HTTP_HEQUEST_H

#include <iscool/http/response.hpp>

#include <functional>
#include <string>

namespace iscool
{
  namespace http
  {
    class request
    {
    public:
      enum class type
      {
        get,
        post
      };

      typedef std::function<void(const response&)> response_handler;

    public:
      void set_type(type t);
      type get_type() const;

      void set_url(const std::string& url);
      const std::string& get_url() const;

      void set_body(const std::string& body);
      const std::string& get_body() const;

      void set_headers(const std::vector<std::string>& headers);
      const std::vector<std::string>& get_headers() const;

      void set_response_handler(response_handler handler);
      response_handler get_response_handler() const;

    private:
      type _type;
      std::string _url;
      std::string _body;
      std::vector<std::string> _headers;
      response_handler _response_handler;
    };
  }
}

#endif
