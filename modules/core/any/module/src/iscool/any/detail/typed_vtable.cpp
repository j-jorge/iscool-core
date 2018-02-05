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
#include "iscool/any/detail/typed_vtable.h"

#include "iscool/any/any.h"

void iscool::any::detail::typed_vtable< void >::clear( any& that )
{

}

void
iscool::any::detail::typed_vtable< void >::copy( any& self, const any& that )
{
    self._value = nullptr;
    self._vtable = that._vtable;
}

void iscool::any::detail::typed_vtable< void >::move( any& self, any&& that )
{
    self._value = nullptr;
    self._vtable = that._vtable;
}
