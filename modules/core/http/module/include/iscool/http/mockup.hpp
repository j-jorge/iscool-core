// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/optional.hpp>

#include <filesystem>
#include <string>
#include <vector>

namespace iscool::http
{
  class mockup
  {
  public:
    mockup();

    void set_enabled(bool enabled);
    bool is_enabled() const;

    void add_predefined_responses(const std::string& path);

    iscool::optional<std::vector<char>>
    get_predefined_response(const std::string& url) const;

  private:
    bool _enabled;
    std::vector<std::filesystem::path> _responses;
  };
}
