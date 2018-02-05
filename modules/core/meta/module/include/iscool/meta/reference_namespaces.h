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
#ifndef ISCOOL_META_REFERENCE_NAMESPACES_H
#define ISCOOL_META_REFERENCE_NAMESPACES_H

#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

#define ic_detail_referenced_namespace_identifier( r, data, i, elem )   \
    elem::

#define ic_reference_namespaces( scope )                        \
    BOOST_PP_SEQ_FOR_EACH_I                                     \
    ( ic_detail_referenced_namespace_identifier, _, scope )

#endif
