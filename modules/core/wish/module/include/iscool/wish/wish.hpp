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
#ifndef WISH_H
#define WISH_H

#include <cstddef>

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>

namespace iscool
{
  namespace wish
  {
    typedef const char* kind;

#define DETAIL_WISH_FIELD_TYPE(seq) BOOST_PP_SEQ_ELEM(0, seq)

#define DETAIL_WISH_FIELD_NAME(seq) BOOST_PP_SEQ_ELEM(1, seq)

#define DETAIL_WISH_MEMBER_NAME(seq)                                          \
  BOOST_PP_CAT(_field, DETAIL_WISH_FIELD_NAME(seq))

#define DETAIL_WISH_CONSTRUCTOR_FIELD(r, data, i, seq)                        \
  BOOST_PP_COMMA_IF(i) DETAIL_WISH_FIELD_TYPE(seq) DETAIL_WISH_FIELD_NAME(seq)

#define DETAIL_WISH_CONSTRUCTOR_FIELD_LIST(fields)                            \
  BOOST_PP_SEQ_FOR_EACH_I(DETAIL_WISH_CONSTRUCTOR_FIELD, _, fields)

#define DETAIL_WISH_CONSTRUCTOR_INITIALIZATION(r, data, i, seq)               \
  BOOST_PP_COMMA_IF(i)                                                        \
  DETAIL_WISH_MEMBER_NAME(seq)(DETAIL_WISH_FIELD_NAME(seq))

#define DETAIL_WISH_CONSTRUCTOR_INITIALIZATION_LIST(fields)                   \
  BOOST_PP_SEQ_FOR_EACH_I(DETAIL_WISH_CONSTRUCTOR_INITIALIZATION, _, fields)

#define DETAIL_WISH_CONSTRUCTOR_IMPL(name, fields)                            \
  name(DETAIL_WISH_CONSTRUCTOR_FIELD_LIST(fields))                            \
    : DETAIL_WISH_CONSTRUCTOR_INITIALIZATION_LIST(fields)                     \
  {}

#define DETAIL_WISH_EMPTY(X, Y)

#define DETAIL_WISH_CONSTRUCTOR(name, fields)                                 \
  BOOST_PP_IF(BOOST_PP_SEQ_SIZE(fields), DETAIL_WISH_CONSTRUCTOR_IMPL,        \
              DETAIL_WISH_EMPTY)                                              \
  (name, fields)

#define DETAIL_WISH_GET_METHOD_NAME(seq)                                      \
  BOOST_PP_CAT(get_, DETAIL_WISH_FIELD_NAME(seq))

#define DETAIL_WISH_GETTER(r, data, seq)                                      \
  DETAIL_WISH_FIELD_TYPE(seq)                                                 \
  DETAIL_WISH_GET_METHOD_NAME(seq)() const                                    \
  {                                                                           \
    return DETAIL_WISH_MEMBER_NAME(seq);                                      \
  }

#define DETAIL_WISH_GETTERS(fields)                                           \
  BOOST_PP_SEQ_FOR_EACH(DETAIL_WISH_GETTER, _, fields)

#define DETAIL_WISH_MEMBER(r, data, seq)                                      \
  DETAIL_WISH_FIELD_TYPE(seq) DETAIL_WISH_MEMBER_NAME(seq);

#define DETAIL_WISH_MEMBERS(fields)                                           \
  BOOST_PP_SEQ_FOR_EACH(DETAIL_WISH_MEMBER, _, fields)

#define DETAIL_WISH_KIND(name)                                                \
  static constexpr iscool::wish::kind kind()                                  \
  {                                                                           \
    return BOOST_PP_STRINGIZE( name );                                          \
  };

#define DECLARE_WISH(name, fields)                                            \
  class name                                                                  \
  {                                                                           \
  public:                                                                     \
    DETAIL_WISH_CONSTRUCTOR(name, fields)                                     \
                                                                              \
  public:                                                                     \
    DETAIL_WISH_GETTERS(fields)                                               \
                                                                              \
  private:                                                                    \
    DETAIL_WISH_MEMBERS(fields)                                               \
                                                                              \
  public:                                                                     \
    DETAIL_WISH_KIND(name)                                                    \
  };

#define DECLARE_SIMPLE_WISH(name) DECLARE_WISH(name, )
  }
}

#endif
