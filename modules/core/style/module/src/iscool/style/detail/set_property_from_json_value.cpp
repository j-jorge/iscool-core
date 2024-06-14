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
#include <iscool/style/detail/set_property_from_json_value.hpp>

#include <iscool/style/loader.hpp>
#include <iscool/style/log_context.hpp>

#include <iscool/style/detail/merge_declarations.hpp>

#include <iscool/style/json/to_declaration.hpp>

#include <iscool/json/cast_bool.hpp>
#include <iscool/json/cast_float.hpp>
#include <iscool/json/cast_string.hpp>
#include <iscool/json/is_of_type_bool.hpp>
#include <iscool/json/is_of_type_float.hpp>
#include <iscool/json/is_of_type_string.hpp>
#include <iscool/log/log.hpp>
#include <iscool/log/nature/info.hpp>

#include <json/value.h>

#include <boost/algorithm/string.hpp>

namespace iscool
{
  namespace style
  {
    namespace detail
    {
      static std::vector<std::string> split_key_path(const std::string& key);

      static std::vector<declaration>
      follow_declarations(const declaration& style,
                          const std::vector<std::string>& keys);

      static void insert_declarations(std::vector<declaration>& declarations,
                                      const std::vector<std::string>& keys);

      static void set_property_value(declaration& style,
                                     const std::string& key,
                                     const Json::Value& property);

      static declaration
      get_merged_json_style_property(const Json::Value& property);
    }
  }
}

void iscool::style::detail::set_property_from_json_value(
    declaration& style, const std::string& key, const Json::Value& property)
{
  const std::vector<std::string> keys(split_key_path(key));

  if (keys.size() == 1)
    set_property_value(style, key, property);
  else
    {
      std::vector<declaration> declarations(follow_declarations(style, keys));

      set_property_value(declarations.back(), keys.back(), property);
      insert_declarations(declarations, keys);

      style = std::move(declarations[0]);
    }
}

std::vector<std::string>
iscool::style::detail::split_key_path(const std::string& key)
{
  std::vector<std::string> keys;
  boost::split(keys, key, boost::is_any_of("/"));
  return keys;
}

std::vector<iscool::style::declaration>
iscool::style::detail::follow_declarations(
    const declaration& style, const std::vector<std::string>& keys)
{
  const std::size_t count(keys.size() - 1);

  std::vector<declaration> result;
  result.reserve(count + 1);
  result.push_back(style);

  for (std::size_t i(0); i != count; ++i)
    result.emplace_back(result.back().get_declaration_or_empty(keys[i]));

  return result;
}

void iscool::style::detail::insert_declarations(
    std::vector<declaration>& declarations,
    const std::vector<std::string>& keys)
{
  const std::size_t count(keys.size() - 1);

  for (std::size_t i(count); i != 0;)
    {
      --i;
      declarations[i].set_declaration(keys[i], declarations[i + 1]);
    }
}

void iscool::style::detail::set_property_value(declaration& style,
                                               const std::string& key,
                                               const Json::Value& property)
{
  if (iscool::json::is_of_type<float>(property))
    style.set_number(key, iscool::json::cast<float>(property));
  else if (iscool::json::is_of_type<bool>(property))
    style.set_boolean(key, iscool::json::cast<bool>(property));
  else if (iscool::json::is_of_type<std::string>(property))
    style.set_string(key, iscool::json::cast<std::string>(property));
  else if (property.isArray())
    style.set_declaration(key, get_merged_json_style_property(property));
  else
    {
      ic_log(iscool::log::nature::info(), log_context(),
             "Invalid property type: %s %d", key, int(property.type()));
      assert(false);
    }
}

iscool::style::declaration
iscool::style::detail::get_merged_json_style_property(
    const Json::Value& property)
{
  const Json::ArrayIndex count(property.size());
  std::vector<declaration> styles;
  styles.reserve(count);

  int i(0);

  for (const Json::Value& value : property)
    {
      if (value.isObject())
        styles.emplace_back(json::to_declaration(value));
      else if (iscool::json::is_of_type<std::string>(value))
        styles.emplace_back(iscool::style::loader::load(
            iscool::json::cast<std::string>(value)));
      else
        {
          ic_log(iscool::log::nature::info(), log_context(),
                 "invalid json value : [ %d ] %d", i, int(value.type()));
          assert(false);
        }

      ++i;
    }

  return merge_declarations(styles);
}
