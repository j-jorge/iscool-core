// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/send.hpp>

#include <iscool/http/detail/get_service_statistics.hpp>
#include <iscool/http/detail/request_handler_pool.hpp>
#include <iscool/http/detail/send_delegate.hpp>
#include <iscool/http/detail/service_statistics.hpp>
#include <iscool/http/get_global_mockup.hpp>
#include <iscool/http/request.hpp>
#include <iscool/schedule/delayed_call.hpp>

namespace iscool::http::detail
{
  static iscool::signals::shared_connection_set
  create_predefined_response_connections(std::vector<char> body,
                                         const response_handler& on_result);

  static iscool::signals::shared_connection_set
  send_get_request(std::string url, response_handler on_result,
                   error_handler on_error);

  static iscool::signals::shared_connection_set
  send_post_request(std::string url, std::vector<std::string> headers,
                    std::string body, response_handler on_result,
                    error_handler on_error);

  static iscool::signals::shared_connection_set
  configure_request(request& output, std::string url,
                    response_handler on_result, error_handler on_error);

  static request_handler_pool handler_pool(16);
}

iscool::signals::shared_connection_set
iscool::http::get(std::string url, response_handler on_result,
                  error_handler on_error)
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

  return detail::send_get_request(std::move(url), std::move(on_result),
                                  std::move(on_error));
}

iscool::signals::shared_connection_set
iscool::http::post(std::string url, std::vector<std::string> headers,
                   std::string body, response_handler on_result,
                   error_handler on_error)
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

  return detail::send_post_request(std::move(url), std::move(headers),
                                   std::move(body), std::move(on_result),
                                   std::move(on_error));
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
          detail::handler_pool.process_response(
              slot_id, response(200, std::move(body)));
        });

  return result;
}

iscool::signals::shared_connection_set iscool::http::detail::send_get_request(
    std::string url, response_handler on_result, error_handler on_error)
{
  assert(detail::send_delegate);

  request r;
  const iscool::signals::shared_connection_set result(
      detail::configure_request(r, std::move(url), std::move(on_result),
                                std::move(on_error)));

  r.request_type = request::type::get;

  detail::send_delegate(std::move(r));

  return result;
}

iscool::signals::shared_connection_set iscool::http::detail::send_post_request(
    std::string url, std::vector<std::string> headers, std::string body,
    response_handler on_result, error_handler on_error)
{
  assert(detail::send_delegate);

  request r;
  const iscool::signals::shared_connection_set result(
      detail::configure_request(r, std::move(url), std::move(on_result),
                                std::move(on_error)));

  r.body = std::move(body);
  r.request_type = request::type::post;
  r.headers = std::move(headers);

  detail::send_delegate(std::move(r));
  return result;
}

iscool::signals::shared_connection_set
iscool::http::detail::configure_request(request& output, std::string url,
                                        response_handler on_result,
                                        error_handler on_error)
{
  get_service_statistics().add_attempt();

  const auto slot(detail::handler_pool.pick_available_handler());

  iscool::signals::shared_connection_set result;

  result.insert(slot.value->connect_to_result(
      [=](std::span<const char> body)
        {
          get_service_statistics().add_success();

          if (on_result)
            on_result(body);
        }));
  result.insert(slot.value->connect_to_error(
      [=](int status, std::span<const char> body)
        {
          get_service_statistics().add_failure();

          if (on_error)
            on_error(status, body);
        }));

  output.url = std::move(url);
  output.result_handler = [id = slot.id](const response& r)
    {
      detail::handler_pool.process_response(id, r);
    };

  return result;
}
