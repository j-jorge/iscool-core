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
#pragma once

#include <iscool/net/byte_array.hpp>
#include <iscool/net/byte_array_reader.hpp>
#include <iscool/net/message/message.hpp>

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

#include <tuple>

namespace iscool
{
  namespace net
  {
    template <message_type type_code, typename... fields_types>
    class raw_message
    {
    private:
      typedef std::tuple<fields_types...> fields_tuple;

    public:
      static message_type get_type();

      void build_message(message& out) const;

    protected:
      explicit raw_message(const std::span<const std::uint8_t>& raw_content);
      explicit raw_message(fields_types... fields);

      template <std::size_t I>
      std::conditional_t<
          std::is_fundamental_v<
              typename std::tuple_element<I, fields_tuple>::type>,
          typename std::tuple_element<I, fields_tuple>::type,
          const typename std::tuple_element<I, fields_tuple>::type&>
      get_field() const;

    private:
      fields_tuple _fields;
    };
  }
}

#include <iscool/net/message/raw_message.tpp>

#define DETAIL_RAW_MESSAGE_GET_FIELD_TYPE(r, data, i, seq)                    \
  BOOST_PP_COMMA_IF(i) BOOST_PP_SEQ_ELEM(0, seq)

#define DETAIL_RAW_MESSAGE_CONSTRUCTOR_ARGUMENT_NAME(name)                    \
  BOOST_PP_CAT(arg, name)

#define DETAIL_RAW_MESSAGE_CREATE_TYPED_CONSTRUCTOR_ARGUMENT(r, data, i, seq) \
  BOOST_PP_COMMA_IF(i)                                                        \
  const BOOST_PP_SEQ_ELEM(0, seq)                                             \
      & DETAIL_RAW_MESSAGE_CONSTRUCTOR_ARGUMENT_NAME(                         \
          BOOST_PP_SEQ_ELEM(1, seq))
#define DETAIL_RAW_MESSAGE_TYPED_CONSTRUCTOR_ARGUMENTS(seq)                   \
  BOOST_PP_SEQ_FOR_EACH_I(                                                    \
      DETAIL_RAW_MESSAGE_CREATE_TYPED_CONSTRUCTOR_ARGUMENT, _, seq)

#define DETAIL_RAW_MESSAGE_CREATE_CONSTRUCTOR_ARGUMENT(r, data, i, seq)       \
  BOOST_PP_COMMA_IF(i)                                                        \
  DETAIL_RAW_MESSAGE_CONSTRUCTOR_ARGUMENT_NAME(BOOST_PP_SEQ_ELEM(1, seq))
#define DETAIL_RAW_MESSAGE_CONSTRUCTOR_ARGUMENTS(seq)                         \
  BOOST_PP_SEQ_FOR_EACH_I(DETAIL_RAW_MESSAGE_CREATE_CONSTRUCTOR_ARGUMENT, _,  \
                          seq)

#define DETAIL_RAW_MESSAGE_IMPLEMENT_GETTER(r, data, i, seq)                  \
  std::conditional_t<std::is_fundamental_v<BOOST_PP_SEQ_ELEM(0, seq)>,        \
                     BOOST_PP_SEQ_ELEM(0, seq),                               \
                     const BOOST_PP_SEQ_ELEM(0, seq)&>                        \
  BOOST_PP_CAT(get_, BOOST_PP_SEQ_ELEM(1, seq))() const                       \
  {                                                                           \
    return get_field<i>();                                                    \
  }

#define DECLARE_RAW_MESSAGE(class_name, type_code, fields)                    \
  class class_name                                                            \
    : public iscool::net::raw_message<                                        \
          type_code BOOST_PP_COMMA_IF(BOOST_PP_SEQ_SIZE(fields))              \
              BOOST_PP_SEQ_FOR_EACH_I(DETAIL_RAW_MESSAGE_GET_FIELD_TYPE, _,   \
                                      fields)>                                \
  {                                                                           \
  private:                                                                    \
    typedef iscool::net::raw_message<                                         \
        type_code BOOST_PP_COMMA_IF(BOOST_PP_SEQ_SIZE(fields))                \
            BOOST_PP_SEQ_FOR_EACH_I(DETAIL_RAW_MESSAGE_GET_FIELD_TYPE, _,     \
                                    fields)>                                  \
        super;                                                                \
                                                                              \
  public:                                                                     \
    class_name(const std::span<const std::uint8_t>& raw_content)              \
      : super(raw_content)                                                    \
    {}                                                                        \
                                                                              \
    class_name(DETAIL_RAW_MESSAGE_TYPED_CONSTRUCTOR_ARGUMENTS(fields))        \
      : super(DETAIL_RAW_MESSAGE_CONSTRUCTOR_ARGUMENTS(fields))               \
    {}                                                                        \
                                                                              \
    BOOST_PP_SEQ_FOR_EACH_I(DETAIL_RAW_MESSAGE_IMPLEMENT_GETTER, , fields)    \
  }

#define DECLARE_EMPTY_RAW_MESSAGE(class_name, type_code)                      \
  DECLARE_RAW_MESSAGE(class_name, type_code, BOOST_PP_EMPTY())
