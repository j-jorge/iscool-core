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
#include "iscool/json/write_to_stream.h"

#include <json/writer.h>

#include <memory>

bool iscool::json::write_to_stream(std::ostream& output,
                                   const Json::Value& value)
{
  Json::StreamWriterBuilder builder;
  builder["commentStyle"] = "None";
  builder["indentation"] = "";
  builder["enableYAMLCompatibility"] = false;
  builder["dropNullPlaceholders"] = false;
  builder["useSpecialFloats"] = false;

  const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

  return writer->write(value, &output) == 0;
}
