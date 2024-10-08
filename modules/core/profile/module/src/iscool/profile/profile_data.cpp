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
#include <iscool/profile/profile_data.hpp>

iscool::profile::profile_data::profile_data()
  : start(std::chrono::milliseconds(0))
  , end(std::chrono::milliseconds(0))
{}

iscool::profile::profile_data::profile_data(
    const std::string& new_name, const std::chrono::milliseconds& new_start,
    const std::chrono::milliseconds& new_end,
    const std::vector<std::string>& new_tags)
  : name(new_name)
  , start(new_start)
  , end(new_end)
  , tags(new_tags)
{}
