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
#include <iscool/style/loader.hpp>

#include <iscool/style/log_context.hpp>

#include <iscool/files/full_path_exists.hpp>
#include <iscool/json/bad_cast.hpp>
#include <iscool/json/cast_string.hpp>
#include <iscool/json/from_file.hpp>
#include <iscool/json/is_member.hpp>
#include <iscool/log/causeless_log.hpp>
#include <iscool/log/nature/error.hpp>
#include <iscool/style/detail/get_style_cache.hpp>
#include <iscool/style/detail/loader_merge_path_list.hpp>
#include <iscool/style/json/to_declaration.hpp>

#include <unordered_set>

namespace iscool
{
  namespace style
  {
    namespace detail
    {
      class loader
      {
      public:
        declaration load_style(const std::string& style_name);

      private:
        declaration open_and_merge(const std::string& style_name);
        declaration
        merge_with_platform_override(const std::string& style_name);

        bool should_be_loaded(const std::string& file_name);

        declaration merge_from_json_file(const std::string& file_name);
        declaration merge_from_json_meta(const Json::Value& meta);

        declaration merge_overrides(const Json::Value& overrides);

      private:
        std::unordered_set<std::string> _loaded;
      };

      static bool _use_global_cache = true;
    }
  }
}

void iscool::style::loader::set_global_cache_enabled(bool enabled)
{
  detail::_use_global_cache = enabled;
}

iscool::style::declaration
iscool::style::loader::load(const std::string& style_name)
{
  return detail::loader().load_style(style_name);
}

iscool::style::declaration
iscool::style::detail::loader::load_style(const std::string& style_name)
{
  _loaded.clear();

  return open_and_merge(style_name);
}

iscool::style::declaration
iscool::style::detail::loader::open_and_merge(const std::string& style_name)
{
  if (!_use_global_cache)
    return merge_with_platform_override(style_name);

  auto& cache(get_style_cache());
  const auto it(cache.find(style_name));

  if (it == cache.end())
    return cache.emplace(style_name, merge_with_platform_override(style_name))
        .first->second;
  else
    return it->second;
}

iscool::style::declaration
iscool::style::detail::loader::merge_with_platform_override(
    const std::string& style_name)
{
  declaration result;

  for (const std::string& path : detail::loader_merge_path_list)
    {
      const std::string_view extension(".json");
      std::string p;
      p.reserve(path.size() + style_name.size() + extension.size());
      p += path;
      p += style_name;
      p += extension;
      result = result.merge(merge_from_json_file(p));
    }

  if (result.is_empty())
    ic_causeless_log(iscool::log::nature::error(), log_context(),
                     "empty style: '%s'.", style_name);

  return result;
}

bool iscool::style::detail::loader::should_be_loaded(
    const std::string& file_name)
{
  if (!_loaded.insert(file_name).second)
    return false;

  if (!iscool::files::full_path_exists(file_name))
    return false;

  return true;
}

iscool::style::declaration iscool::style::detail::loader::merge_from_json_file(
    const std::string& file_name)
{
  if (!should_be_loaded(file_name))
    return declaration();

  const Json::Value value(iscool::json::from_file(file_name));

  declaration result;

  if (iscool::json::is_member("meta", value))
    result = result.merge(merge_from_json_meta(value["meta"]));

  if (iscool::json::is_member("style", value))
    result = result.merge(json::to_declaration(value["style"]));

  return result;
}

iscool::style::declaration
iscool::style::detail::loader::merge_from_json_meta(const Json::Value& meta)
{
  if (!meta.isObject())
    {
      ic_causeless_log(iscool::log::nature::error(), log_context(),
                       "meta is not a json object.");
      return declaration();
    }

  return merge_overrides(meta["overrides"]);
}

iscool::style::declaration
iscool::style::detail::loader::merge_overrides(const Json::Value& overrides)
{
  if (overrides.isNull())
    return declaration();

  if (!overrides.isArray())
    {
      ic_causeless_log(iscool::log::nature::error(), log_context(),
                       "overrides is not a json array.");
      return declaration();
    }

  const std::size_t size(overrides.size());
  declaration result;

  for (std::size_t i(0); i != size; ++i)
    {
      Json::Value override(overrides[Json::ArrayIndex(i)]);

      try
        {
          result = result.merge(
              open_and_merge(iscool::json::cast<std::string>(override)));
        }
      catch (iscool::json::bad_cast& e)
        {
          ic_causeless_log(iscool::log::nature::error(), log_context(),
                           "override value '%s' is not a string.",
                           override.toStyledString());
        }
    }

  return result;
}
