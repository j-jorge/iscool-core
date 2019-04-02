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
#ifndef ISCOOL_STYLE_DETAIL_DECLARATION_REF_H
#define ISCOOL_STYLE_DETAIL_DECLARATION_REF_H

#include "iscool/style/detail/properties_handle.h"

#include <type_traits>

namespace iscool
{
    namespace style
    {
        class declaration;

        namespace detail
        {
            class declaration_ref
            {
            public:
                declaration_ref();
                declaration_ref( const declaration_ref& that );
                declaration_ref( declaration_ref&& that );
                ~declaration_ref();
                
                declaration_ref& operator=( const declaration_ref& that );
                declaration_ref& operator=( declaration_ref&& that );

                declaration& operator*();
                const declaration& operator*() const;
                
                declaration* operator->();
                const declaration* operator->() const;

                operator declaration& ();
                operator const declaration& () const;
                
            private:
                std::aligned_storage< sizeof( properties_handle ) >::type
                _storage;
            };
        }
    }
}

#endif

