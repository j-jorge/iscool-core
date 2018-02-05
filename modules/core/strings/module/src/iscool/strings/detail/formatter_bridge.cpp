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
#include "iscool/strings/detail/formatter_bridge.h"

#include "iscool/memory/global_thread_safe_pool.h"
#include "iscool/memory/global_thread_safe_pool.impl.tpp"
#include "iscool/strings/detail/formatter.h"

iscool::strings::detail::formatter*
iscool::strings::detail::create_formatter( const std::string& pattern )
{
    return
        iscool::memory::get_global_thread_safe_pool< formatter >()
        .construct( pattern );
}

void iscool::strings::detail::release_formatter( formatter* f )
{
    iscool::memory::get_global_thread_safe_pool< formatter >().destroy( f );
}

std::string iscool::strings::detail::get_formatter_string( const formatter& f )
{
    return f.string();
}

template< typename T >
int iscool::strings::detail::append_to_formatter( formatter& f, T value )
{
    f.append( value );
    return 0;
}

template int iscool::strings::detail::append_to_formatter< const char* >
( formatter& f, const char* value );
template int iscool::strings::detail::append_to_formatter< const std::string& >
( formatter& f, const std::string& value );
template int iscool::strings::detail::append_to_formatter< std::string >
( formatter& f, std::string value );
template int iscool::strings::detail::append_to_formatter< int >
( formatter& f, int value );
template int iscool::strings::detail::append_to_formatter< unsigned int >
( formatter& f, unsigned int value );
template int iscool::strings::detail::append_to_formatter< long >
( formatter& f, long value );
template int iscool::strings::detail::append_to_formatter< unsigned long >
( formatter& f, unsigned long value );
template int iscool::strings::detail::append_to_formatter< long long >
( formatter& f, long long value );
template int iscool::strings::detail::append_to_formatter< unsigned long long >
( formatter& f, unsigned long long value );
template int iscool::strings::detail::append_to_formatter< float >
( formatter& f, float value );
template int iscool::strings::detail::append_to_formatter< double >
( formatter& f, double value );
