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
#include "iscool/locale/character_range.h"

#include <cstring>

#ifdef ISCOOL_HAS_BOOST_LOCALE
#include <boost/locale/generator.hpp>
#else
#include <stdexcept>
#endif

#ifdef ISCOOL_HAS_BOOST_LOCALE
iscool::locale::character_range iscool::locale::make_character_range
( const std::string& text )
{
    static const std::locale locale( boost::locale::generator()("en.UTF-8") );

    return
        character_range
        ( boost::locale::boundary::character, text.begin(), text.end(),
          locale );
}

#else

iscool::locale::character_range
iscool::locale::make_character_range( const std::string& text )
{
    throw
        std::runtime_error
        ( "iscool::locale::make_character_range is not supported on this"
          " platform." );
    
    return character_range();
}

#endif
