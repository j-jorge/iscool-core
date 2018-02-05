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
#ifndef ISCOOL_NET_BYTE_ARRAY_BIT_READER_H
#define ISCOOL_NET_BYTE_ARRAY_BIT_READER_H

namespace iscool
{
    namespace net
    {
        class byte_array_reader;

        class byte_array_bit_reader
        {
        public:
            explicit byte_array_bit_reader( byte_array_reader& array );
            
            std::uint8_t get( std::uint8_t bit_count );

        private:
            void fill_buffer();
            
        private:
            byte_array_reader& _array;
            std::uint8_t _buffer;
            std::uint8_t _available_bits;
        };
    }
}

#endif
