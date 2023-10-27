#include <iscool/strings/hash.hpp>

std::size_t iscool::strings::hash::operator()(const char* s) const
{
  return hash_type()(s);
}

std::size_t iscool::strings::hash::operator()(std::string_view s) const
{
  return hash_type()(s);
}

std::size_t iscool::strings::hash::operator()(const std::string& s) const
{
  return hash_type()(s);
}
