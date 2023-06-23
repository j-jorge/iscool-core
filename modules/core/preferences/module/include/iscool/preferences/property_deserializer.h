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
#ifndef ISCOOL_PREFERENCES_PROPERTY_DESERIALIZER_H
#define ISCOOL_PREFERENCES_PROPERTY_DESERIALIZER_H

#include "iscool/preferences/property_map.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace iscool
{
  namespace preferences
  {
    class property_deserializer
    {
    public:
      void add_int64_property(const std::string& key);
      void add_bool_property(const std::string& key);
      void add_float_property(const std::string& key);
      void add_string_property(const std::string& key);

      void remove_int64_property(const std::string& key);
      void remove_bool_property(const std::string& key);
      void remove_float_property(const std::string& key);
      void remove_string_property(const std::string& key);

      std::vector<std::string> get_all_keys() const;

      void merge(const property_deserializer& that);

      void operator()(property_map& result,
                      const std::unordered_map<std::string, std::string>&
                          properties) const;

    private:
      void add_key(std::unordered_set<std::string>& domain,
                   const std::string& key);

      void set_int64_value(const std::string& key, const std::string& value,
                           property_map& result) const;

      void set_bool_value(const std::string& key, const std::string& value,
                          property_map& result) const;

      void set_float_value(const std::string& key, const std::string& value,
                           property_map& result) const;

      void set_string_value(const std::string& key, const std::string& value,
                            property_map& result) const;

    private:
      std::unordered_set<std::string> _int64;
      std::unordered_set<std::string> _bool;
      std::unordered_set<std::string> _float;
      std::unordered_set<std::string> _string;
    };
  }
}

#endif
