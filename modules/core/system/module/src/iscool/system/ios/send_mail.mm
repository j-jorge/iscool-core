/* -*- objc -*- */
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
#include <iscool/system/send_mail.hpp>

#include <iscool/ios/get_root_view_controller.hpp>
#include <iscool/ios/std_to_nsstring.hpp>
#include <iscool/log/causeless_log.hpp>
#include <iscool/log/nature/warning.hpp>

#import <MessageUI/MessageUI.h>

@interface mail_composer_delegate:
    NSObject< MFMailComposeViewControllerDelegate >

@property ( nonatomic, retain ) mail_composer_delegate* self_reference;

- (void) mailComposeController: ( MFMailComposeViewController* ) controller
           didFinishWithResult: ( MFMailComposeResult ) result
                         error: ( NSError* ) error;

@end

@implementation mail_composer_delegate

@synthesize self_reference;

- (void) mailComposeController: ( MFMailComposeViewController* ) controller
           didFinishWithResult: ( MFMailComposeResult ) result
                         error: ( NSError* ) error
{
    [ controller dismissViewControllerAnimated: YES completion: nil ];
    self_reference = nullptr;
}

@end

void iscool::system::send_mail
( const std::string& address, const std::string& subject,
  const std::string& body )
{
    if ( ![ MFMailComposeViewController canSendMail ] )
    {
        ic_causeless_log
            ( iscool::log::nature::warning(), "iscool::system::send_mail",
              "This device cannot send an e-mail." );
        return;
    }

    MFMailComposeViewController* const view_controller
        ( [ MFMailComposeViewController new ] );

    mail_composer_delegate* const delegate( [ mail_composer_delegate new ] );
    delegate.self_reference = delegate;
    
    view_controller.mailComposeDelegate = delegate;
    [ view_controller setSubject: iscool::ios::std_to_nsstring( subject ) ];
    [ view_controller setMessageBody: iscool::ios::std_to_nsstring( body )
                              isHTML: NO ];
        
    [ view_controller
      setToRecipients: @[ iscool::ios::std_to_nsstring( address ) ] ];
        
    [ iscool::ios::get_root_view_controller()
      presentViewController: view_controller
      animated:YES
      completion:NULL ];
}
