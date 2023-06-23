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
#ifndef ISCOOL_STYLE_DETAIL_SHARED_PROPERTIES_H
#define ISCOOL_STYLE_DETAIL_SHARED_PROPERTIES_H

#include <iscool/style/detail/properties.hpp>

namespace iscool
{
  namespace style
  {
    namespace detail
    {
      class shared_properties
      {
      public:
        shared_properties();

        shared_properties(const shared_properties& that) = delete;
        shared_properties& operator=(const shared_properties& that) = delete;

        std::uint64_t get_id() const;
        void reuse();

        void add_reference();
        void remove_reference();
        bool is_dangling();
        std::size_t get_use_count() const;

      public:
        properties values;

      private:
        void set_id();

      private:
        static std::uint64_t _next_id;
        std::uint64_t _id;

        std::size_t _reference_count;
      };
    }
  }
}

#endif
