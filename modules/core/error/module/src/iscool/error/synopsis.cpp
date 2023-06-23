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
#include "iscool/error/synopsis.h"

iscool::error::synopsis::synopsis(std::size_t code,
                                  const std::string& category,
                                  const std::string& title,
                                  const std::string& message)
  : m_code(code)
  , m_category(category)
  , m_title(title)
  , m_message(message)
{}

std::size_t iscool::error::synopsis::get_code() const
{
  return m_code;
}

const std::string& iscool::error::synopsis::get_category() const
{
  return m_category;
}

const std::string& iscool::error::synopsis::get_title() const
{
  return m_title;
}

const std::string& iscool::error::synopsis::get_message() const
{
  return m_message;
}
