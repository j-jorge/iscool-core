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
#ifndef ISCOOL_COLLECTIONS_INSERT_OR_ASSIGN_ALL_TPP
#define ISCOOL_COLLECTIONS_INSERT_OR_ASSIGN_ALL_TPP

#include <tuple>

template <typename OutputContainer, typename InputContainer>
void iscool::collections::insert_or_assign_all(OutputContainer& output,
                                               const InputContainer& input)
{
  bool inserted;
  typename OutputContainer::iterator iterator;

  for (const auto& e : input)
    {
      std::tie(iterator, inserted) = output.insert(e);

      if (!inserted)
        iterator->second = e.second;
    }
}

#endif
