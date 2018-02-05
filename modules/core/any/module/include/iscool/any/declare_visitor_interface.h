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
#ifndef ISCOOL_ANY_DECLARE_VISITOR_INTERFACE_H
#define ISCOOL_ANY_DECLARE_VISITOR_INTERFACE_H

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

#include <tuple>

#define ic_any_detail_function_call_operator( r, data, i, type )        \
    void operator()( const type& );

#define ic_any_declare_visitor_interface( types )                             \
    typedef std::tuple< BOOST_PP_SEQ_ENUM( types ) > supported_types;         \
    BOOST_PP_SEQ_FOR_EACH_I( ic_any_detail_function_call_operator, _, types ) \
    void visit( std::size_t type_id, void* value )                            \

#endif

