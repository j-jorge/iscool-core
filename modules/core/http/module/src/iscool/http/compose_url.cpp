// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/compose_url.hpp>

#include <iscool/http/url_encode.hpp>

std::string
iscool::http::compose_url(std::string_view root,
                          const std::vector<query_parameter>& parameters)
{
  if (parameters.empty())
    return std::string(root);

  std::string result(root);
  result += '?';

  const auto eit(parameters.end());
  auto query(parameters.begin());

  result += query->key;
  result += '=';
  result += url_encode(query->value);

  for (++query; query != eit; ++query)
    {
      result += '&';
      result += query->key;
      result += '=';
      result += url_encode(query->value);
    }

  return result;
}
