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
#ifndef ISCOOL_STYLE_JSON_FROM_DECLARATION_H
#define ISCOOL_STYLE_JSON_FROM_DECLARATION_H

#include "json/value.h"

namespace iscool
{
  namespace style
  {
    class declaration;

    namespace json
    {
      Json::Value from_declaration(const iscool::style::declaration&);
    }
  }
}

#endif
