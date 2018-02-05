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
#ifndef ISCOOL_ANY_IMPLEMENT_VISITOR_INTERFACE_H
#define ISCOOL_ANY_IMPLEMENT_VISITOR_INTERFACE_H

#include "iscool/any/detail/get_visitors.h"

#define ic_any_implement_visitor_interface( visitor )                   \
    void visitor::visit( std::size_t type_id, void* value )             \
    {                                                                   \
        static const auto visitors                                      \
            ( ::iscool::any::detail::get_visitors                       \
              <                                                         \
                visitor&,                                               \
                visitor::supported_types                                \
              >() );                                                    \
        static const auto end( visitors.end() );                        \
                                                                        \
        const auto it( visitors.find( type_id ) );                      \
                                                                        \
        if ( it != end )                                                \
            it->second( value, *this );                                 \
    }

#endif
