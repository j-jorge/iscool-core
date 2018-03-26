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
#include "iscool/i18n/detail/assign_plural_index.h"

#include "iscool/i18n/detail/plural_index.h"

#define assign_index_expression_and_return( expression )        \
    {                                                           \
        plural_index =                                          \
            []( std::uint64_t n ) -> std::uint8_t               \
            {                                                   \
                return expression;                              \
            };                                                  \
                                                                \
        return;                                                 \
    }

void
iscool::i18n::detail::assign_plural_index( const std::string& language_code )
{
    /*
      See the table on this page for updates:
      http://localization-guide.readthedocs.org/en/latest/l10n/pluralforms.html
    */
    
    if ( ( language_code == "fr" )
         || ( language_code == "pt_BR" )
         || ( language_code == "tr" ) )
        assign_index_expression_and_return( ( n > 1 ) ? 1 : 0 );

    if ( ( language_code == "de" )
         || ( language_code == "en" )
         || ( language_code == "es" )
         || ( language_code == "fi" )
         || ( language_code == "it" )
         || ( language_code == "nl" )
         || ( language_code == "pt" )
         || ( language_code == "sv" ) )
        assign_index_expression_and_return( ( n != 1 ) ? 1 : 0 );

    if ( ( language_code == "ja" )
         || ( language_code == "ko" )
         || ( language_code == "th" )
         || ( language_code == "zh_CN" )
         || ( language_code == "zh_TW" ) )
        assign_index_expression_and_return( 0 );

    if ( language_code == "pl" )
        assign_index_expression_and_return
            ( ( n == 1 )
              ? 0
              : ( ( n % 10 >= 2 ) && ( n % 10 <= 4 )
                  && ( ( n % 100 < 10 ) || ( n % 100 >= 20 ) )
                  ? 1
                  : 2 ) );
    
    if ( language_code == "ru" )
        assign_index_expression_and_return
            ( ( ( n % 10 == 1 ) && ( n % 100 != 11 ) )
              ? 0
              : ( ( n % 10 >= 2 ) && ( n % 10 <= 4 )
                  && ( ( n % 100 < 10 ) || ( n % 100 >= 20 ) )
                  ? 1
                  : 2 ) );
    
    assert( false );
}

#undef assign_index_expression_and_return
