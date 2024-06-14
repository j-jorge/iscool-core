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
#ifndef ISCOOL_PREFERENCES_DETAIL_GET_GLOBAL_PROPERTY_TPP
#define ISCOOL_PREFERENCES_DETAIL_GET_GLOBAL_PROPERTY_TPP

#include <iscool/preferences/detail/global_properties.hpp>
#include <iscool/preferences/log_context.hpp>

#include <iscool/log/log.hpp>
#include <iscool/log/nature/error.hpp>

#include <boost/lexical_cast.hpp>

template <typename T>
T iscool::preferences::detail::get_global_property(const property<T>& property)
{
  static int version(0);
  static std::unordered_map<std::string, T> cache;

  const int current_version(detail::get_global_properties_version());

  if (version != current_version)
    {
      cache.clear();
      version = current_version;
    }

  const std::string& property_name(property.name);
  const auto cache_it(cache.find(property_name));

  if (cache_it != cache.end())
    return cache_it->second;

  const std::unordered_map<std::string, std::string>& properties(
      detail::get_global_properties());
  const auto it(properties.find(property_name));

  if (it == properties.end())
    return property.fallback;

  try
    {
      const T result(boost::lexical_cast<T>(it->second));
      cache.emplace(property_name, result);
      return result;
    }
  catch (const boost::bad_lexical_cast& e)
    {
      ic_log(iscool::log::nature::error(), log_context(),
             "Failed to convert global property value '%s=%s': %s",
             property_name, it->second, e.what());
    }

  return property.fallback;
}

#endif
