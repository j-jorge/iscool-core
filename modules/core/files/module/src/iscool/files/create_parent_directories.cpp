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
#include "iscool/files/create_parent_directories.h"

#include "iscool/files/log_context.h"

#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/error.h"

#include <boost/filesystem/operations.hpp>

bool iscool::files::create_parent_directories( const std::string& path )
{
    const boost::filesystem::path parent_path
        ( boost::filesystem::path( path ).parent_path() );
    boost::system::error_code error;
    
    boost::filesystem::create_directories( path );

    if ( !error )
        return true;

    ic_causeless_log
        ( iscool::log::nature::error(), log_context(),
          "Could not create directory '%s' for '%s': %s", parent_path.string(),
          path, error.message() );

    return false;
}
