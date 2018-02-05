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
#ifndef ISCOOL_ANY_DETAIL_TYPED_VTABLE_TPP
#define ISCOOL_ANY_DETAIL_TYPED_VTABLE_TPP

#include "iscool/any/any.h"
#include "iscool/any/detail/get_vtable.h"

#include "iscool/memory/global_pool.h"
#include "iscool/memory/global_pool.impl.tpp"

template< typename T >
void iscool::any::detail::typed_vtable< T >::clear( any& that )
{
    iscool::memory::get_global_pool< T >().destroy
        ( reinterpret_cast< T* >( that._value ) );
    that._vtable = get_vtable< void >();
}

template< typename T >
void iscool::any::detail::typed_vtable< T >::copy( any& self, const any& that )
{
    if ( that._value != nullptr )
        self._value =
            iscool::memory::get_global_pool< T >().construct
            ( *reinterpret_cast< T* >( that._value ) );
    else
        self._value = nullptr;

    self._vtable = that._vtable;
}

template< typename T >
void iscool::any::detail::typed_vtable< T >::move( any& self, any&& that )
{
    self._value = that._value;
    self._vtable = that._vtable;
    that._vtable = get_vtable< void >();
}

#endif
