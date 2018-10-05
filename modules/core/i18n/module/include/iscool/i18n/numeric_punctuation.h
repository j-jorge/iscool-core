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
#ifndef ISCOOL_I18N_NUMERIC_PUNCTUATION_H
#define ISCOOL_I18N_NUMERIC_PUNCTUATION_H

#include <locale>

namespace iscool
{
    namespace i18n
    {
        class numeric_punctuation:
            public std::numpunct<char>
        {
        public:
            numeric_punctuation
            ( char decimal_point, char thousands_separator,
              std::string grouping );
            
        private:
            char do_decimal_point() const override;
            char do_thousands_sep() const override;
            std::string do_grouping() const override;

        private:
            char _decimal_point;
            char _thousands_separator;
            std::string _grouping;
        };
    }
}

#endif
