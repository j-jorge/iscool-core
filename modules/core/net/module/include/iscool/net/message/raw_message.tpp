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
#include <iscool/net/byte_array_serialization/byte_array_serialization.hpp>
#include <iscool/net/byte_array_serialization/byte_array_tuple_serialization.hpp>

template <iscool::net::message_type type_code, typename... fields_types>
iscool::net::message_type
iscool::net::raw_message<type_code, fields_types...>::get_type()
{
  return type_code;
}

template <iscool::net::message_type type_code, typename... fields_types>
void iscool::net::raw_message<type_code, fields_types...>::build_message(
    message& out) const
{
  out.reset(get_type());
  out.get_content() << _fields;
}

template <iscool::net::message_type type_code, typename... fields_types>
iscool::net::raw_message<type_code, fields_types...>::raw_message(
    const std::span<const std::uint8_t>& raw_content)
{
  byte_array_reader reader(raw_content);
  reader >> _fields;
}

template <iscool::net::message_type type_code, typename... fields_types>
iscool::net::raw_message<type_code, fields_types...>::raw_message(
    fields_types... fields)
  : _fields{ fields... }
{}

template <iscool::net::message_type type_code, typename... fields_types>
template <std::size_t I>
std::conditional_t<
    std::is_fundamental_v<typename std::tuple_element<
        I, typename iscool::net::raw_message<
               type_code, fields_types...>::fields_tuple>::type>,
    typename std::tuple_element<
        I, typename iscool::net::raw_message<
               type_code, fields_types...>::fields_tuple>::type,
    const typename std::tuple_element<
        I, typename iscool::net::raw_message<
               type_code, fields_types...>::fields_tuple>::type&>
iscool::net::raw_message<type_code, fields_types...>::get_field() const
{
  return std::get<I>(_fields);
}
