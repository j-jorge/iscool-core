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
#include <iscool/system/language_code.hpp>

#import <Foundation/Foundation.h>

std::string iscool::system::get_language_code()
{
    NSString* const language
        ( [ [ NSLocale preferredLanguages ] objectAtIndex: 0 ] );

    NSDictionary* const components
        ( [ NSLocale componentsFromLocaleIdentifier: language ] );

    NSString* const language_code
      ( [ components objectForKey: NSLocaleLanguageCode ] );
    
    return [ language_code UTF8String ];
}
