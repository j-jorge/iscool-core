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

namespace iscool
{
  namespace net
  {
    namespace detail
    {
      template <typename tuple>
      class tuple_reader_helper;

      template <std::size_t I, typename tuple>
      class tuple_reader_helper_base;

      template <std::size_t I>
      class tuple_reader_helper_base<I, std::tuple<>>
      {
      public:
        void read_values(byte_array_reader& reader, std::tuple<>& tuple) const
        {}
        void write_values(byte_array& output, const std::tuple<>& tuple) const
        {}
      };

      template <typename... T>
      class tuple_reader_helper_base<0, std::tuple<T...>>
      {
      public:
        void read_values(byte_array_reader& reader,
                         std::tuple<T...>& tuple) const;
        void write_values(byte_array& output,
                          const std::tuple<T...>& tuple) const;
      };

      template <std::size_t I, typename... T>
      class tuple_reader_helper_base<I, std::tuple<T...>>
      {
      public:
        void read_values(byte_array_reader& reader,
                         std::tuple<T...>& tuple) const;
        void write_values(byte_array& output,
                          const std::tuple<T...>& tuple) const;
      };

      template <typename... T>
      class tuple_reader_helper<std::tuple<T...>>
        : public tuple_reader_helper_base<sizeof...(T) - 1, std::tuple<T...>>
      {};
    }
  }
}

template <typename... T>
iscool::net::byte_array& iscool::net::operator<<(byte_array& output,
                                                 const std::tuple<T...>& value)
{
  detail::tuple_reader_helper<std::tuple<T...>> helper;
  helper.write_values(output, value);
  return output;
}

template <typename... T>
iscool::net::byte_array_reader&
iscool::net::operator>>(byte_array_reader& input, std::tuple<T...>& value)
{
  detail::tuple_reader_helper<std::tuple<T...>> helper;
  helper.read_values(input, value);
  return input;
}

template <typename... T>
void iscool::net::detail::tuple_reader_helper_base<
    0, std::tuple<T...>>::read_values(byte_array_reader& reader,
                                      std::tuple<T...>& tuple) const
{
  reader >> std::get<0>(tuple);
}

template <typename... T>
void iscool::net::detail::tuple_reader_helper_base<
    0, std::tuple<T...>>::write_values(byte_array& output,
                                       const std::tuple<T...>& tuple) const
{
  output << std::get<0>(tuple);
}

template <std::size_t I, typename... T>
void iscool::net::detail::tuple_reader_helper_base<
    I, std::tuple<T...>>::read_values(byte_array_reader& reader,
                                      std::tuple<T...>& tuple) const
{
  tuple_reader_helper_base<I - 1, std::tuple<T...>> helper;
  helper.read_values(reader, tuple);

  reader >> std::get<I>(tuple);
}

template <std::size_t I, typename... T>
void iscool::net::detail::tuple_reader_helper_base<
    I, std::tuple<T...>>::write_values(byte_array& output,
                                       const std::tuple<T...>& tuple) const
{
  tuple_reader_helper_base<I - 1, std::tuple<T...>> helper;
  helper.write_values(output, tuple);

  output << std::get<I, T...>(tuple);
}
