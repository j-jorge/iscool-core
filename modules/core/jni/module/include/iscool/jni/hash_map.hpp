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
#ifndef ISCOOL_JNI_HASH_MAP_H
#define ISCOOL_JNI_HASH_MAP_H

#include <iscool/jni/map_entry.hpp>

#include <vector>

namespace iscool
{
  namespace jni
  {
    template <typename K, typename V>
    class hash_map
    {
    public:
      typedef java_ptr<K> key_type;
      typedef java_ptr<V> value_type;

    public:
      hash_map();
      explicit hash_map(const java_ptr<jobject>& impl);

      const java_ptr<jobject>& get_java_object() const;

      value_type put(const key_type& key, const value_type& value) const;

      std::vector<map_entry<K, V>> get_entry_set() const;

    private:
      java_ptr<jobject> _map;
    };

    namespace detail
    {
      template <typename K, typename V>
      struct get_method_argument_impl<hash_map<K, V>>
      {
        static jobject get(const hash_map<K, V>& array);
      };
    }
  }
}

#include <iscool/jni/detail/hash_map.tpp>

#endif
