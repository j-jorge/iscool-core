// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/send.hpp>

#include <iscool/http/detail/request_handler_pool.hpp>
#include <iscool/http/detail/send_delegate.hpp>
#include <iscool/http/get_global_mockup.hpp>
#include <iscool/http/request.hpp>
#include <iscool/http/response.hpp>
#include <iscool/schedule/delayed_call.hpp>

namespace iscool::http::detail
{
  static iscool::http::request_connection
  create_predefined_response_connections(std::vector<char> body,
                                         const response_handler& on_result);

  static iscool::http::request_connection
  send_get_request(const std::string& url, response_handler on_result,
                   error_handler on_error);

  static iscool::http::request_connection
  send_post_request(const std::string& url, std::vector<std::string> headers,
                    std::string body, response_handler on_result,
                    error_handler on_error);

  static iscool::http::request_connection
  configure_request(request*& output, const std::string& url,
                    response_handler on_result, error_handler on_error);

  static void process_response(std::size_t handler_index, const response& r);

  static request_handler_pool g_handler_pool(16);
}

iscool::http::request_connection iscool::http::get(const std::string& url,
                                                   response_handler on_result,
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

iscool::http::request_connection
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

iscool::http::request_connection
iscool::http::detail::create_predefined_response_connections(
    std::vector<char> body, const response_handler& on_result)
{
  iscool::http::request_connection result;

  const detail::request_handler_pool::slot slot =
      g_handler_pool.pick_available_handler();

  result.result = slot.value->on_result.connect(on_result);

  iscool::schedule::delayed_call(
      [body = std::move(body), slot_id = slot.id]()
        {
          process_response(slot_id, response(200, std::move(body)));
        });

  return result;
}

iscool::http::request_connection iscool::http::detail::send_get_request(
    const std::string& url, response_handler on_result, error_handler on_error)
{
  assert(detail::send_delegate);

  request* r;
  const iscool::http::request_connection result(detail::configure_request(
      r, url, std::move(on_result), std::move(on_error)));

  r->request_type = request::type::get;

  detail::send_delegate(*r);

  return result;
}

iscool::http::request_connection iscool::http::detail::send_post_request(
    const std::string& url, std::vector<std::string> headers, std::string body,
    response_handler on_result, error_handler on_error)
{
  assert(detail::send_delegate);

  request* r;
  const iscool::http::request_connection result(detail::configure_request(
      r, url, std::move(on_result), std::move(on_error)));

  r->body = std::move(body);
  r->request_type = request::type::post;
  r->headers = std::move(headers);

  detail::send_delegate(*r);

  return result;
}

iscool::http::request_connection iscool::http::detail::configure_request(
    request*& request, const std::string& url, response_handler on_result,
    error_handler on_error)
{
  const auto slot(g_handler_pool.pick_available_handler());
  request_handler& handler = *slot.value;
  request = &handler.request;

  iscool::http::request_connection connections;

  if (on_result)
    connections.result = handler.on_result.connect(on_result);

  if (on_error)
    connections.error = handler.on_error.connect(on_error);

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
