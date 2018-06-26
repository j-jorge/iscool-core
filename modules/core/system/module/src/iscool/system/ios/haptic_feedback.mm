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
#include "iscool/system/haptic_feedback.h"

#include "iscool/schedule/delayed_call.h"
#include "iscool/system/haptic_feedback_notification.h"

#include <UIKit/UIKit.h>

#include <cassert>

namespace iscool
{
    namespace system
    {
        namespace detail
        {
            constexpr const std::chrono::milliseconds
            wait_for_feedback_duration( 500 );
        }
    }
}

iscool::system::haptic_feedback::haptic_feedback()
    : _notification_generator( nullptr ),
      _selection_generator( nullptr ),
      _low_impact_generator( nullptr ),
      _medium_impact_generator( nullptr ),
      _heavy_impact_generator( nullptr )
{
}

iscool::system::haptic_feedback::~haptic_feedback() = default;

void iscool::system::haptic_feedback::prepare_notification()
{
    ensure_notification_generator_exists();
    [ _notification_generator prepare ];
}

void iscool::system::haptic_feedback::emit_notification
( haptic_feedback_notification feedback, bool keep_prepared )
{
    ensure_notification_generator_exists();

    UINotificationFeedbackType type;
    switch( feedback )
    {
    case haptic_feedback_notification::success:
        type = UINotificationFeedbackTypeSuccess;
        break;
    case haptic_feedback_notification::warning:
        type = UINotificationFeedbackTypeWarning;
        break;
    case haptic_feedback_notification::failure:
        type = UINotificationFeedbackTypeError;
        break;
    default:
        assert( false );
    }

    [ _notification_generator notificationOccurred:type ];

    if( keep_prepared )
        [ _notification_generator prepare ];
}

void iscool::system::haptic_feedback::prepare_selection()
{
    ensure_selection_generator_exists();
    [ _selection_generator prepare ];
}

void iscool::system::haptic_feedback::emit_selection
( bool keep_prepared )
{
    ensure_selection_generator_exists();
    [ _selection_generator selectionChanged ];

    if( keep_prepared )
        [ _selection_generator prepare ];
}

void iscool::system::haptic_feedback::prepare_low_impact()
{
    ensure_low_impact_generator_exists();
    [ _low_impact_generator prepare ];
}

void iscool::system::haptic_feedback::emit_low_impact( bool keep_prepared )
{
    ensure_low_impact_generator_exists();
    [ _low_impact_generator impactOccurred ];

    if( keep_prepared )
        [ _low_impact_generator prepare ];
}

void iscool::system::haptic_feedback::prepare_medium_impact()
{
    ensure_medium_impact_generator_exists();
    [ _medium_impact_generator prepare ];
}

void iscool::system::haptic_feedback::emit_medium_impact( bool keep_prepared )
{
    ensure_medium_impact_generator_exists();
    [ _medium_impact_generator impactOccurred ];

    if( keep_prepared )
        [ _medium_impact_generator prepare ];
}

void iscool::system::haptic_feedback::prepare_heavy_impact()
{
    ensure_heavy_impact_generator_exists();
    [ _heavy_impact_generator prepare ];
}

void iscool::system::haptic_feedback::emit_heavy_impact( bool keep_prepared )
{
    ensure_heavy_impact_generator_exists();
    [ _heavy_impact_generator impactOccurred ];

    if( keep_prepared )
        [ _heavy_impact_generator prepare ];
}

void iscool::system::haptic_feedback::ensure_notification_generator_exists()
{
    if( _notification_generator == nullptr )
        _notification_generator =
            [ [ UINotificationFeedbackGenerator alloc ] init ];

    _notification_connection = iscool::schedule::delayed_call
        ( [ this ] () -> void { _notification_generator = nullptr; },
          detail::wait_for_feedback_duration );
}

void iscool::system::haptic_feedback::ensure_selection_generator_exists()
{
    if( _selection_generator == nullptr )
        _selection_generator =
            [ [ UISelectionFeedbackGenerator alloc ] init ];

    _selection_connection = iscool::schedule::delayed_call
        ( [ this ] () -> void { _selection_generator = nullptr; },
          detail::wait_for_feedback_duration );
}

void iscool::system::haptic_feedback::ensure_low_impact_generator_exists()
{
    if( _low_impact_generator == nullptr )
        _low_impact_generator =
            [ [ UIImpactFeedbackGenerator alloc ]
              initWithStyle:UIImpactFeedbackStyleMedium ];

    _low_impact_connection = iscool::schedule::delayed_call
        ( [ this ] () -> void { _low_impact_generator = nullptr; },
          detail::wait_for_feedback_duration );
}

void iscool::system::haptic_feedback::ensure_medium_impact_generator_exists()
{
    if( _medium_impact_generator == nullptr )
        _medium_impact_generator =
            [ [ UIImpactFeedbackGenerator alloc ]
              initWithStyle:UIImpactFeedbackStyleMedium ];

    _medium_impact_connection = iscool::schedule::delayed_call
        ( [ this ] () -> void { _medium_impact_generator = nullptr; },
          detail::wait_for_feedback_duration );
}

void iscool::system::haptic_feedback::ensure_heavy_impact_generator_exists()
{
    if( _heavy_impact_generator == nullptr )
        _heavy_impact_generator =
            [ [ UIImpactFeedbackGenerator alloc ]
              initWithStyle:UIImpactFeedbackStyleMedium ];

    _heavy_impact_connection = iscool::schedule::delayed_call
        ( [ this ] () -> void { _heavy_impact_generator = nullptr; },
          detail::wait_for_feedback_duration );
}

