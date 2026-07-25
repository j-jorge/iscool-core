// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/json/send.hpp>

#include <iscool/http/json/headers.hpp>

#include <iscool/http/send.hpp>

#include <iscool/json/parse_string.hpp>

namespace iscool::http::json::detail
{
  static http::response_handler
  build_json_result_handler(response_handler on_result,
                            http::error_handler on_error);
}

iscool::signals::shared_connection_set
iscool::http::json::get(const std::string& url, response_handler on_result,
                        http::error_handler on_error)
{
  http::response_handler convert_result_to_json(
      detail::build_json_result_handler(std::move(on_result), on_error));

  return http::get(url, std::move(convert_result_to_json),
                   std::move(on_error));
}

iscool::signals::shared_connection_set
iscool::http::json::post(const std::string& url, const Json::Value& body,
                         response_handler on_result,
                         http::error_handler on_error)
{
  std::string body_data(body.toStyledString());
  http::response_handler convert_result_to_json(
      detail::build_json_result_handler(std::move(on_result), on_error));

  std::vector<std::string> headers;
  headers.reserve(2);
  headers.emplace_back(headers::content_type);
  headers.emplace_back(headers::accept);

  return http::post(url, std::move(headers), std::move(body_data),
                    std::move(convert_result_to_json), std::move(on_error));
}

iscool::http::response_handler
iscool::http::json::detail::build_json_result_handler(
    response_handler on_result, http::error_handler on_error)
{
  return [on_result = std::move(on_result), on_error = std::move(on_error)](
             std::span<const char> response) -> void
           {
             if (response.empty())
               {
                 on_result(Json::nullValue);
                 return;
               }

             on_result(iscool::json::parse_string(
                 std::string_view(response.data(), response.size())));
           };
}
