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
#ifndef ISCOOL_LOCALE_CHARACTER_RANGE_H
#define ISCOOL_LOCALE_CHARACTER_RANGE_H

#ifdef ISCOOL_HAS_BOOST_LOCALE
  #include <boost/locale/boundary/index.hpp>
#else
  #include <vector>
#endif

#include <string>

namespace iscool
{
  namespace locale
  {
#ifdef ISCOOL_HAS_BOOST_LOCALE
    typedef boost::locale::boundary::ssegment_index character_range;
#else
    typedef std::vector<std::string> character_range;
#endif

    character_range make_character_range(const std::string& text);
  }
}

#endif
