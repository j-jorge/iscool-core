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
#ifndef ISCOOL_STYLE_DETAIL_PROPERTIES_HANDLE_H
#define ISCOOL_STYLE_DETAIL_PROPERTIES_HANDLE_H

#include <cstddef>
#include <cstdint>

namespace iscool
{
  namespace style
  {
    namespace detail
    {
      class properties;
      class shared_properties;

      class properties_handle
      {
      public:
        properties_handle();
        properties_handle(const properties_handle& that);
        properties_handle(properties_handle&& that);
        ~properties_handle();

        properties_handle& operator=(const properties_handle& that);
        properties_handle& operator=(properties_handle&& that);

        explicit operator bool() const;

        properties* operator->() const;
        properties& operator*() const;

        std::uint64_t get_id() const;

        void alloc();
        void reset();

        bool is_unique() const;

      private:
        std::size_t _pool_id;
        shared_properties* _properties;
      };
    }
  }
}

#endif
