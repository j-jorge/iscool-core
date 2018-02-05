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
#ifndef ISCOOL_PREFERENCES_LOCAL_PREFERENCES_TPP
#define ISCOOL_PREFERENCES_LOCAL_PREFERENCES_TPP

#include "iscool/files/file_exists.h"
#include "iscool/json/from_file.h"
#include "iscool/preferences/detail/local_preferences_from_json.h"
#include <boost/bind.hpp>

template< typename Rep, typename Period >
iscool::preferences::local_preferences::local_preferences
( const std::chrono::duration< Rep, Period >& flush_delay,
  const std::string& file_path )
    : _file_path( file_path ),
      _values
      ( iscool::files::file_exists( _file_path )
        ? iscool::json::from_file( _file_path )
        : Json::Value() ),
      _store( flush_delay, detail::local_preferences_from_json( _values ),
              boost::bind( &local_preferences::save, this, _1 ) )
{
    
}

#endif
