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
#ifndef ISCOOL_STYLE_DEEP_MUTATE_TPP
#define ISCOOL_STYLE_DEEP_MUTATE_TPP

#include "iscool/style/declaration.h"

template <typename Mutation, std::size_t N>
void iscool::style::deep_mutate(declaration& style,
                                const std::array<std::string, N>& path,
                                Mutation mutation)
{
  static constexpr std::size_t queue_size(N + 1);
  std::array<declaration, queue_size> queue{ { style } };

  for (std::size_t i(0); i != N; ++i)
    queue[i + 1] = queue[i].get_declaration_or_empty(path[i]);

  mutation(queue.back());

  for (std::size_t i(queue_size - 1); i != 0; --i)
    queue[i - 1].set_declaration(path[i - 1], queue[i]);

  style = std::move(queue.front());
}

#endif
