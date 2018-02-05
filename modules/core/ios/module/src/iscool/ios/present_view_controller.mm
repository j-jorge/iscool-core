/* -*- c++ -*- */
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
#include "iscool/ios/present_view_controller.h"

#import <UIKit/UIViewController.h>
#import <UIKit/UIPopoverPresentationController.h>
#import <UIKit/UIWindow.h>

void iscool::ios::present_view_controller( UIViewController* controller )
{
    UIWindow* const key_window
        ( [ [ UIApplication sharedApplication ] keyWindow ] );
    UIViewController* const view_controller
        ( [ key_window rootViewController ] );
    
    if ( [ controller
             respondsToSelector: @selector( popoverPresentationController ) ] )
    {
        UIView* const view( [ view_controller view ] );
        
        controller.modalPresentationStyle = UIModalPresentationPopover;
        controller.popoverPresentationController.sourceView = view;
        
        CGRect rect;
        rect.size = view.bounds.size;
        rect.origin.x = 0;
        rect.origin.y = rect.size.height;
        
        controller.popoverPresentationController.sourceRect = rect;
    }
    
    [ view_controller presentViewController: controller
      animated: YES
      completion: nil ];
}
