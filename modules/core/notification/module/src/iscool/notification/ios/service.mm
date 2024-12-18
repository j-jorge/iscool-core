/* -*- mode: objc -*- */
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
#include <iscool/notification/ios/service.hpp>

#include <iscool/ios/std_to_nsstring.hpp>
#include <iscool/log/log.hpp>
#include <iscool/log/nature/error.hpp>

#import <UIKit/UIApplication.h>
#import <UIKit/UIUserNotificationSettings.h>
#import <UserNotifications/UserNotifications.h>

void iscool::notification::ios::service::enable_notifications()
{
    UIApplication* const application( [ UIApplication sharedApplication ] );

    if ( [ application
           respondsToSelector:@selector( registerUserNotificationSettings: ) ] )
    {
        // Register for Push Notifications for iOS 8
        const UIUserNotificationType userNotificationTypes =
            UIUserNotificationTypeAlert
            | UIUserNotificationTypeBadge
            | UIUserNotificationTypeSound;
        UIUserNotificationSettings* const settings =
            [ UIUserNotificationSettings settingsForTypes: userNotificationTypes
                                               categories: nil ];
        [ application registerUserNotificationSettings:settings ];
        [ application registerForRemoteNotifications ];
    }
    else
    {
        // Register for Push Notifications for iOS 7
        const UIRemoteNotificationType remoteNotificationTypes =
            UIRemoteNotificationTypeBadge
            | UIRemoteNotificationTypeAlert
            | UIRemoteNotificationTypeSound;
        [ application
            registerForRemoteNotificationTypes: remoteNotificationTypes ];
    }
}

bool
iscool::notification::ios::service::are_notifications_enabled() const
{
    UIApplication* const application( [ UIApplication sharedApplication ] );

    if ( [ application
           respondsToSelector:
                 @selector( isRegisteredForRemoteNotifications ) ] )
        return
            [ [ UIApplication sharedApplication ]
                isRegisteredForRemoteNotifications ];
    else
    {
        const UIRemoteNotificationType types
            ( [ application enabledRemoteNotificationTypes ] );

        return ( types & UIRemoteNotificationTypeAlert ) != 0;
    }
}

void iscool::notification::ios::service::schedule
( std::size_t id, const std::chrono::seconds& delay, const std::string& title,
  const std::string& message )
{
    UNMutableNotificationContent* const content
        ( [ UNMutableNotificationContent new ] );
    
    content.body = iscool::ios::std_to_nsstring( message );

    UNTimeIntervalNotificationTrigger* const trigger
        ( [ UNTimeIntervalNotificationTrigger
                     triggerWithTimeInterval: delay.count()
                                     repeats: NO] );

    NSString* const id_string( [ NSString stringWithFormat: @"%lu", id ] );

    UNNotificationRequest* const request
        ( [ UNNotificationRequest
            requestWithIdentifier: id_string
                          content: content
                          trigger: trigger] );

    UNUserNotificationCenter* const center
        ( [ UNUserNotificationCenter currentNotificationCenter ] );
    
    [ center addNotificationRequest: request
              withCompletionHandler: ^( NSError* error )
             {
                 if ( error != nil )
                     ic_log
                         ( iscool::log::nature::error(),
                           "iscool::notification::ios::service",
                           "schedule",
                           "code={}, domain={}, {}", error.code,
                           error.domain.UTF8String,
                           error.localizedDescription.UTF8String );
             }
      ];
}

void iscool::notification::ios::service::cancel_all()
{
    [ [ UNUserNotificationCenter currentNotificationCenter ]
        removeAllPendingNotificationRequests ];
}

