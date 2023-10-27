#pragma once

#include <iscool/strings/hash.hpp>

#include <unordered_map>

namespace iscool::strings
{
  template <typename V>
  using unordered_string_map =
    std::unordered_map<std::string, V, iscool::strings::hash, std::equal_to<>>;
}
