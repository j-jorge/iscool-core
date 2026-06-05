// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/query_parameter.hpp>

#include <string_view>
#include <vector>

namespace iscool::http
{
  std::string compose_url(std::string_view root,
                          const std::vector<query_parameter>& parameters);
}
