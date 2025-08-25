// SPDX-License-Identifier: Apache-2.0
#include <iscool/system/language_name.hpp>

#import <Foundation/Foundation.h>

std::string iscool::system::get_language_name()
{
    NSString* const language
        ( [ [ NSLocale preferredLanguages ] objectAtIndex: 0 ] );

    NSDictionary* const components
        ( [ NSLocale componentsFromLocaleIdentifier: language ] );

    NSString* const language_name
      ( [ components objectForKey: NSLocaleLanguageCode ] );

    return iscool::from_string_with_fallback([ language_name UTF8String ]);
}
