// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/style/detail/properties_handle.hpp>

#include <cstddef>
#include <type_traits>

namespace iscool::style
{
  class declaration;

  namespace detail
  {
    class declaration_ref
    {
    public:
      declaration_ref();
      declaration_ref(const declaration_ref& that);
      declaration_ref(declaration_ref&& that);
      ~declaration_ref();

      declaration_ref& operator=(const declaration_ref& that);
      declaration_ref& operator=(declaration_ref&& that);

      declaration& operator*();
      const declaration& operator*() const;

      declaration* operator->();
      const declaration* operator->() const;

      operator declaration&();
      operator const declaration&() const;

    private:
      alignas(properties_handle) std::byte _storage[sizeof(properties_handle)];
    };
  }
}
