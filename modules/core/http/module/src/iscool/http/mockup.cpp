/*
  Copyright 2018-present IsCool Entertainment

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#include <iscool/http/mockup.hpp>

#include <iscool/files/get_full_path.hpp>
#include <iscool/files/read_file.hpp>
#include <iscool/json/from_file.hpp>
#include <iscool/json/is_member.hpp>
#include <iscool/none.hpp>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace iscool
{
  namespace http
  {
    namespace detail
    {
      static iscool::optional<std::vector<char>>
      get_predefined_response(const Json::Value& responses,
                              const std::string& url);

      static iscool::optional<std::vector<char>>
      get_file_content(const std::string& path);
    }
  }
}

iscool::http::mockup::mockup()
  : _enabled(false)
{}

void iscool::http::mockup::set_enabled(bool enabled)
{
  _enabled = true;
}

bool iscool::http::mockup::is_enabled() const
{
  return _enabled;
}

void iscool::http::mockup::add_predefined_responses(const std::string& path)
{
  _responses.push_back(path);
}

iscool::optional<std::vector<char>>
iscool::http::mockup::get_predefined_response(const std::string& url) const
{
  const auto end(_responses.rend());

  for (auto it(_responses.rbegin()); it != end; ++it)
    {
      const iscool::optional<std::vector<char>> result(
          detail::get_predefined_response(iscool::json::from_file(*it), url));

      if (result)
        return result;
    }

  return iscool::none;
}

iscool::optional<std::vector<char>>
iscool::http::detail::get_predefined_response(const Json::Value& responses,
                                              const std::string& url)
{
  std::string clean_url(url);
  const std::string::size_type separator(clean_url.find_first_of('?'));

  if (separator != std::string::npos)
    clean_url.erase(clean_url.begin() + separator, clean_url.end());

  std::vector<std::string> path;
  boost::split(path, clean_url, boost::is_any_of("/"),
               boost::token_compress_on);

  const std::size_t count(path.size());
  assert(count >= 3);

  Json::Value candidate(responses);

  for (std::size_t i(1); i != count; ++i)
    {
      const std::string& p(path[i]);

      assert(candidate.isObject());

      if (iscool::json::is_member(p, candidate))
        candidate = candidate[p];
      else
        return iscool::none;
    }

  assert(candidate.isString());
  return detail::get_file_content(candidate.asString());
}

iscool::optional<std::vector<char>>
iscool::http::detail::get_file_content(const std::string& path)
{
  const std::unique_ptr<std::istream> content(
      iscool::files::read_file(iscool::files::get_full_path(path)));

  if ((content == nullptr) || !(*content))
    return iscool::none;

  content->seekg(0, std::ios_base::end);
  const std::streampos size(content->tellg());

  std::vector<char> result(size);

  content->seekg(0, std::ios_base::beg);
  content->read(&result[0], size);

  return result;
}
