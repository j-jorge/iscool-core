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
#include "iscool/social/share_service.h"

void iscool::social::share_service::share_message( const std::string& message )
{
    _impl.share_message( message );
}

void iscool::social::share_service::share_file
( const std::string& file_path, const std::string& message )
{
    _impl.share_file( file_path, message );
}
