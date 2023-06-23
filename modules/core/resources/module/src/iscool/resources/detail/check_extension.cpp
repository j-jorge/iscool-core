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
#include <iscool/resources/detail/check_extension.hpp>

std::string::size_type
iscool::resources::detail::check_extension(const std::string& extension,
                                           const std::string& filename)
{
  const std::string::size_type extension_size(extension.size());
  const std::string::size_type filename_size(filename.size());

  if (filename_size < extension_size)
    return std::string::npos;

  const std::string::size_type result(filename_size - extension_size);

  if (std::equal(extension.begin(), extension.end(),
                 filename.begin() + result))
    return result;

  return std::string::npos;
}
