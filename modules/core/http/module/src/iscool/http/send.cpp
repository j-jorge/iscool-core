// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/send.hpp>

#include <iscool/http/detail/get_service_statistics.hpp>
#include <iscool/http/detail/request_handler_pool.hpp>
#include <iscool/http/detail/send_delegate.hpp>
#include <iscool/http/detail/service_statistics.hpp>
#include <iscool/http/get_global_mockup.hpp>
#include <iscool/http/request.hpp>
#include <iscool/http/response.hpp>
#include <iscool/schedule/delayed_call.hpp>

namespace iscool::http::detail
{
  static iscool::signals::shared_connection_set
  create_predefined_response_connections(std::vector<char> body,
                                         const response_handler& on_result);

  static iscool::signals::shared_connection_set
  send_get_request(const std::string& url, response_handler on_result,
                   error_handler on_error);

  static iscool::signals::shared_connection_set
  send_post_request(const std::string& url, std::vector<std::string> headers,
                    std::string body, response_handler on_result,
                    error_handler on_error);

  static iscool::signals::shared_connection_set
  configure_request(request*& output, const std::string& url,
                    response_handler on_result, error_handler on_error);

  static void process_response(std::size_t handler_index, const response& r);

  static request_handler_pool g_handler_pool(16);
}

iscool::signals::shared_connection_set
iscool::http::get(const std::string& url, response_handler on_result,
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

  return detail::send_get_request(url, std::move(on_result),
                                  std::move(on_error));
}

iscool::signals::shared_connection_set
iscool::http::post(const std::string& url, std::vector<std::string> headers,
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

  return detail::send_post_request(url, std::move(headers), std::move(body),
                                   std::move(on_result), std::move(on_error));
}

iscool::signals::shared_connection_set
iscool::http::detail::create_predefined_response_connections(
    std::vector<char> body, const response_handler& on_result)
{
  iscool::signals::shared_connection_set result;

  const detail::request_handler_pool::slot slot =
      g_handler_pool.pick_available_handler();

  result.insert(slot.value->on_result.connect(on_result));

  iscool::schedule::delayed_call(
      [body = std::move(body), slot_id = slot.id]()
        {
          process_response(slot_id, response(200, std::move(body)));
        });

  return result;
}

iscool::signals::shared_connection_set iscool::http::detail::send_get_request(
    const std::string& url, response_handler on_result, error_handler on_error)
{
  assert(detail::send_delegate);

  request* r;
  const iscool::signals::shared_connection_set result(
      detail::configure_request(r, url, std::move(on_result),
                                std::move(on_error)));

  r->request_type = request::type::get;

  detail::send_delegate(*r);

  return result;
}

iscool::signals::shared_connection_set iscool::http::detail::send_post_request(
    const std::string& url, std::vector<std::string> headers, std::string body,
    response_handler on_result, error_handler on_error)
{
  assert(detail::send_delegate);

  request* r;
  const iscool::signals::shared_connection_set result(
      detail::configure_request(r, url, std::move(on_result),
                                std::move(on_error)));

  r->body = std::move(body);
  r->request_type = request::type::post;
  r->headers = std::move(headers);

  detail::send_delegate(*r);

  return result;
}

iscool::signals::shared_connection_set iscool::http::detail::configure_request(
    request*& request, const std::string& url, response_handler on_result,
    error_handler on_error)
{
  get_service_statistics().add_attempt();

  const auto slot(g_handler_pool.pick_available_handler());
  request_handler& handler = *slot.value;
  request = &handler.request;

  iscool::signals::shared_connection_set connections;

  connections.insert(handler.on_result.connect(
      [=](std::span<const char> body)
        {
          get_service_statistics().add_success();

          if (on_result)
            on_result(body);
        }));
  connections.insert(handler.on_error.connect(
      [=](int status, std::span<const char> body)
        {
          get_service_statistics().add_failure();

          if (on_error)
            on_error(status, body);
        }));

  request->url = url;
  request->result_handler = [id = slot.id](const response& r)
    {
      process_response(id, r);
    };

  return connections;
}

void iscool::http::detail::process_response(std::size_t handler_index,
                                            const response& r)
{
  request_handler& handler = g_handler_pool.get(handler_index);

  if (r.status == 200)
    {
      handler.on_result(r.body);
      g_handler_pool.release(handler_index);
      return;
    }

  if (((r.status == 408)     /* timeout */
       || (r.status == 502)  /* bad gateway */
       || (r.status == 503)  /* service unavailable */
       || (r.status == 504)) /* gateway timeout */
      && (handler.retry_delay < std::chrono::seconds(5))
      && (!handler.on_result.empty() || !handler.on_error.empty()))
    {
      handler.retry_connection = iscool::schedule::delayed_call(
          [handler_index]()
            {
              detail::send_delegate(g_handler_pool.get(handler_index).request);
            },
          handler.retry_delay);
      handler.retry_delay += std::chrono::seconds(1);
      return;
    }

  handler.on_error(r.status, r.body);
  g_handler_pool.release(handler_index);
}
