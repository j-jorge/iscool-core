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
#include <iscool/http/send.hpp>

#include <iscool/http/detail/get_service_statistics.hpp>
#include <iscool/http/detail/request_handler_pool.hpp>
#include <iscool/http/detail/send_delegate.hpp>
#include <iscool/http/detail/service_statistics.hpp>
#include <iscool/http/get_global_mockup.hpp>
#include <iscool/http/request.hpp>
#include <iscool/schedule/delayed_call.hpp>

namespace iscool
{
  namespace http
  {
    namespace detail
    {
      static iscool::signals::shared_connection_set
      create_predefined_response_connections(
          std::vector<char> body, const response_handler& on_result);

      static iscool::signals::shared_connection_set
      send_get_request(const std::string& url,
                       const response_handler& on_result,
                       const response_handler& on_error);

      static iscool::signals::shared_connection_set send_post_request(
          const std::string& url, const std::vector<std::string>& headers,
          const std::string& body, const response_handler& on_result,
          const response_handler& on_error);

      static iscool::signals::shared_connection_set
      configure_request(request& output, const std::string& url,
                        response_handler on_result, response_handler on_error);

      static request_handler_pool handler_pool(16);
    }
  }
}

iscool::signals::shared_connection_set
iscool::http::get(const std::string& url, response_handler on_result,
                  response_handler on_error)
{
  const mockup& http_mockup(get_global_mockup());

  if (http_mockup.is_enabled())
    {
      const iscool::optional<std::vector<char>> predefined_response(
          http_mockup.get_predefined_response(url));

      if (predefined_response)
        return detail::create_predefined_response_connections(
            std::move(*predefined_response), on_result);
    }

  return detail::send_get_request(url, on_result, on_error);
}

iscool::signals::shared_connection_set
iscool::http::post(const std::string& url,
                   const std::vector<std::string>& headers,
                   const std::string& body, response_handler on_result,
                   response_handler on_error)
{
  const mockup& http_mockup(get_global_mockup());

  if (http_mockup.is_enabled())
    {
      const iscool::optional<std::vector<char>> predefined_response(
          http_mockup.get_predefined_response(url));

      if (predefined_response)
        return detail::create_predefined_response_connections(
            std::move(*predefined_response), on_result);
    }

  return detail::send_post_request(url, headers, body, on_result, on_error);
}

iscool::signals::shared_connection_set
iscool::http::detail::create_predefined_response_connections(
    std::vector<char> body, const response_handler& on_result)
{
  iscool::signals::shared_connection_set result;

  const detail::request_handler_pool::slot slot =
      detail::handler_pool.pick_available_handler();

  result.insert(slot.value->connect_to_result(on_result));

  iscool::schedule::delayed_call(
      [body = std::move(body), slot_id = slot.id]()
      {
        detail::handler_pool.process_response(slot_id, response(200, body));
      });

  return result;
}

iscool::signals::shared_connection_set
iscool::http::detail::send_get_request(const std::string& url,
                                       const response_handler& on_result,
                                       const response_handler& on_error)
{
  assert(detail::send_delegate);

  request r;
  const iscool::signals::shared_connection_set result(
      detail::configure_request(r, url, on_result, on_error));

  r.set_type(request::type::get);

  detail::send_delegate(r);

  return result;
}

iscool::signals::shared_connection_set iscool::http::detail::send_post_request(
    const std::string& url, const std::vector<std::string>& headers,
    const std::string& body, const response_handler& on_result,
    const response_handler& on_error)
{
  assert(detail::send_delegate);

  request r;
  const iscool::signals::shared_connection_set result(
      detail::configure_request(r, url, on_result, on_error));

  r.set_body(body);
  r.set_type(request::type::post);
  r.set_headers(headers);

  detail::send_delegate(r);
  return result;
}

iscool::signals::shared_connection_set iscool::http::detail::configure_request(
    request& output, const std::string& url, response_handler on_result,
    response_handler on_error)
{
  get_service_statistics().add_attempt();

  const auto slot(detail::handler_pool.pick_available_handler());

  const auto tag_success(
      std::bind(&service_statistics::add_success, &get_service_statistics()));
  const auto tag_failure(
      std::bind(&service_statistics::add_failure, &get_service_statistics()));

  slot.value->connect_to_result(tag_success);
  slot.value->connect_to_error(tag_failure);

  iscool::signals::shared_connection_set result;

  result.insert(slot.value->connect_to_result(on_result));
  result.insert(slot.value->connect_to_error(on_error));

  output.set_url(url);
  output.set_response_handler(
      std::bind(&request_handler_pool::process_response, &detail::handler_pool,
                slot.id, std::placeholders::_1));

  return result;
}
