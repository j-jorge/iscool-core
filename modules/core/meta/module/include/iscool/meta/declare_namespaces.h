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
#ifndef ISCOOL_META_DECLARE_NAMESPACES_H
#define ISCOOL_META_DECLARE_NAMESPACES_H

#include <boost/preprocessor/seq/for_each_i.hpp>

#define ic_detail_open_namespace( r, data, i, elem ) \
    namespace elem {

#define ic_detail_close_namespace( r, data, i, elem )   \
    }

#define ic_open_namespaces( scope )                             \
    BOOST_PP_SEQ_FOR_EACH_I                                     \
    ( ic_detail_open_namespace, _, scope )

#define ic_close_namespaces( scope )                             \
    BOOST_PP_SEQ_FOR_EACH_I                                      \
    ( ic_detail_close_namespace, _, scope )

#endif
