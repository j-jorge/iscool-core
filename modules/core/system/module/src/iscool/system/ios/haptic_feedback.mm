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

#include "iscool/ios/get_device_model.h"
#include "iscool/ios/system_version.h"
#include "iscool/schedule/delayed_call.h"
#include "iscool/system/haptic_feedback_notification.h"

#include <UIKit/UIKit.h>

#include <cassert>
#include <unordered_set>

namespace iscool
{
    namespace system
    {
        namespace detail
        {
            constexpr const std::chrono::milliseconds
            wait_for_feedback_duration( 500 );

            static bool is_haptic_feedback_available();
        }
    }
}

iscool::system::haptic_feedback::haptic_feedback()
    : _available( detail::is_haptic_feedback_available() ),
      _enabled( _available ),
      _notification_generator( nullptr ),
      _selection_generator( nullptr ),
      _low_impact_generator( nullptr ),
      _medium_impact_generator( nullptr ),
      _heavy_impact_generator( nullptr )
{
}

iscool::system::haptic_feedback::~haptic_feedback() = default;

bool iscool::system::haptic_feedback::is_available() const
{
    return _available;
}

bool iscool::system::haptic_feedback::is_enabled() const
{
    return _enabled;
}

void iscool::system::haptic_feedback::set_enabled( bool enabled )
{
    if( !is_available() )
        return;

    _enabled = enabled;
}

void iscool::system::haptic_feedback::prepare_notification()
{
    if( !is_enabled() )
        return;

    ensure_notification_generator_exists();
    [ _notification_generator prepare ];
}

void iscool::system::haptic_feedback::emit_notification
( haptic_feedback_notification feedback, bool keep_prepared )
{
    if( !is_enabled() )
        return;

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
    if( !is_enabled() )
        return;

    ensure_selection_generator_exists();
    [ _selection_generator prepare ];
}

void iscool::system::haptic_feedback::emit_selection
( bool keep_prepared )
{
    if( !is_enabled() )
        return;

    ensure_selection_generator_exists();
    [ _selection_generator selectionChanged ];

    if( keep_prepared )
        [ _selection_generator prepare ];
}

void iscool::system::haptic_feedback::prepare_low_impact()
{
    if( !is_enabled() )
        return;

    ensure_low_impact_generator_exists();
    [ _low_impact_generator prepare ];
}

void iscool::system::haptic_feedback::emit_low_impact( bool keep_prepared )
{
    if( !is_enabled() )
        return;

    ensure_low_impact_generator_exists();
    [ _low_impact_generator impactOccurred ];

    if( keep_prepared )
        [ _low_impact_generator prepare ];
}

void iscool::system::haptic_feedback::prepare_medium_impact()
{
    if( !is_enabled() )
        return;

    ensure_medium_impact_generator_exists();
    [ _medium_impact_generator prepare ];
}

void iscool::system::haptic_feedback::emit_medium_impact( bool keep_prepared )
{
    if( !is_enabled() )
        return;

    ensure_medium_impact_generator_exists();
    [ _medium_impact_generator impactOccurred ];

    if( keep_prepared )
        [ _medium_impact_generator prepare ];
}

void iscool::system::haptic_feedback::prepare_heavy_impact()
{
    if( !is_enabled() )
        return;

    ensure_heavy_impact_generator_exists();
    [ _heavy_impact_generator prepare ];
}

void iscool::system::haptic_feedback::emit_heavy_impact( bool keep_prepared )
{
    if( !is_enabled() )
        return;

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

bool iscool::system::detail::is_haptic_feedback_available()
{
    if ( !iscool::ios::system_version_is_at_least( "10.0" ) )
        return false;

    const std::unordered_set< std::string > haptic_enabled_models
        ( { "iPhone9,1",   // iPhone 7
            "iPhone9,3",   // iPhone 7
            "iPhone9,2",   // iPhone 7 Plus
            "iPhone9,4",   // iPhone 7 Plus
            "iPhone10,1",  // iPhone 8
            "iPhone10,4",  // iPhone 8
            "iPhone10,2",  // iPhone 8 Plus
            "iPhone10,5",  // iPhone 8 Plus
            "iPhone10,3",  // iPhone X
            "iPhone10,6"   // iPhone X
        } );

    const std::string model( iscool::ios::get_device_model() );
    return haptic_enabled_models.find( model ) != haptic_enabled_models.end();
}
