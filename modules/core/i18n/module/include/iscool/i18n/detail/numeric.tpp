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
#ifndef ISCOOL_I18N_NUMERIC_TPP
#define ISCOOL_I18N_NUMERIC_TPP

#include "iscool/i18n/english_numeric_punctuation.h"
#include "iscool/i18n/detail/num_put_disambiguation.h"

#include <sstream>

template< typename T >
typename std::enable_if
<
    std::is_integral< T >::value,
    std::string
>::type
iscool::i18n::numeric::to_string( const T& value )
{
    std::ostringstream formatter;
    
    formatter.imbue
        ( std::locale
          ( formatter.getloc(), new english_numeric_punctuation() ) );

    const std::num_put<char>& facet
        ( std::use_facet< std::num_put<char> >( formatter.getloc() ) );

    facet.put
        ( std::ostreambuf_iterator<char>(formatter), formatter, ' ',
          static_cast< typename detail::num_put_disambiguation< T >::type >
          ( value ) );

    return formatter.str();
}

#endif
