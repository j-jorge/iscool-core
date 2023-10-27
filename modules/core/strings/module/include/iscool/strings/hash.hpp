#pragma once

#include <string>
#include <string_view>

namespace iscool::strings
{
  class hash
  {
  public:
    using hash_type = std::hash<std::string_view>;
    using is_transparent = void;

    std::size_t operator()(const char* s) const;
    std::size_t operator()(std::string_view s) const;
    std::size_t operator()(const std::string& s) const;
  };
}
