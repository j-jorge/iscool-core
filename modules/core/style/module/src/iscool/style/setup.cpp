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
#include "iscool/style/setup.h"

#include "iscool/style/detail/get_properties_pool.h"
#include "iscool/style/detail/get_style_cache.h"
#include "iscool/style/detail/loader_merge_path_list.h"
#include "iscool/style/detail/shared_properties.h"

#include <cassert>

void iscool::style::initialize(const merge_path_list& path_list)
{
  assert(!path_list.empty());
  assert(detail::loader_merge_path_list.empty());
  detail::loader_merge_path_list = path_list;
}

void iscool::style::finalize()
{
  assert(!detail::loader_merge_path_list.empty());
  detail::loader_merge_path_list.clear();

  detail::get_style_cache().clear();
  detail::get_properties_pool().clear();
}
