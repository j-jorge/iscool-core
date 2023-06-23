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
#ifndef ISCOOL_STYLE_DECLARATION_H
#define ISCOOL_STYLE_DECLARATION_H

#include "iscool/optional.h"
#include "iscool/style/detail/declaration_ref.h"
#include "iscool/style/detail/properties_handle.h"

#include <boost/range/iterator_range.hpp>

#include <string>
#include <unordered_map>

namespace iscool
{
  namespace style
  {
    class declaration
    {
    public:
      typedef std::unordered_map<std::string, float> numbers_map;
      typedef std::unordered_map<std::string, bool> booleans_map;

      typedef std::unordered_map<std::string, detail::declaration_ref>
          declaration_map;

      typedef std::unordered_map<std::string, std::string> string_map;

      template <typename T>
      using range = boost::iterator_range<T>;
      typedef range<numbers_map::const_iterator> numbers_range;
      typedef range<booleans_map::const_iterator> booleans_range;
      typedef range<string_map::const_iterator> strings_range;
      typedef range<declaration_map::const_iterator> declarations_range;

    public:
      void set_number(const std::string& key, float value);
      iscool::optional<float> get_number(const std::string& key) const;
      float get_number(const std::string& key, float default_value) const;

      void set_boolean(const std::string& key, bool value);
      iscool::optional<bool> get_boolean(const std::string& key) const;
      bool get_boolean(const std::string& key, bool default_value) const;

      void set_string(const std::string& key, const std::string& value);
      iscool::optional<const std::string&>
      get_string(const std::string& key) const;
      std::string get_string(const std::string& key,
                             const std::string& default_value) const;

      void set_declaration(const std::string& key, const declaration& style);
      iscool::optional<const declaration&>
      get_declaration(const std::string& key) const;
      const declaration&
      get_declaration_or_empty(const std::string& key) const;

      declaration merge(declaration style) const;

      bool is_empty() const;

      numbers_range get_numbers() const;
      booleans_range get_booleans() const;
      strings_range get_strings() const;
      declarations_range get_declarations() const;

      std::size_t get_declaration_count() const;

      std::uint64_t get_id() const;

    private:
      declaration_map get_merged_declarations(const declaration& style) const;

      void ensure_owned_properties();

    private:
      detail::properties_handle _properties;
    };
  }
}

#endif
