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
#include "iscool/system/detail/haptic_feedback_mockup.h"

#include "iscool/log/console_log.h"
#include "iscool/system/haptic_feedback_notification.h"

#include <cassert>

bool iscool::system::haptic_feedback::is_available() const
{
    return false;
}

bool iscool::system::haptic_feedback::is_enabled() const
{
    return false;
}

void iscool::system::haptic_feedback::set_enabled( bool enabled )
{
    ic_console_log
        ( "iscool::system", "Set haptic feedback enabled: %1%.",
          enabled ? "true" : "false" );
}

void iscool::system::haptic_feedback::prepare_notification()
{
    ic_console_log( "iscool::system", "Prepare notification haptic feedback" );
}

void iscool::system::haptic_feedback::emit_notification
( haptic_feedback_notification feedback, bool keep_prepared )
{
    std::string feedback_name;
    
    switch( feedback )
    {
    case haptic_feedback_notification::success:
        feedback_name = "success";
        break;
    case haptic_feedback_notification::warning:
        feedback_name = "warning";
        break;
    case haptic_feedback_notification::failure:
        feedback_name = "failure";
        break;
    default:
        assert( false );
    }
    
    ic_console_log
        ( "iscool::system", "Haptic feedback '%1%'.", feedback_name );

    if( keep_prepared )
        prepare_notification();
}

void iscool::system::haptic_feedback::prepare_selection()
{
    ic_console_log( "iscool::system", "Prepare selection haptic feedback" );
}

void iscool::system::haptic_feedback::emit_selection( bool keep_prepared )
{
    ic_console_log
        ( "iscool::system", "Haptic feedback 'selection changed'." );

    if( keep_prepared )
        prepare_selection();
}

void iscool::system::haptic_feedback::prepare_low_impact()
{
    ic_console_log( "iscool::system", "Prepare low impact haptic feedback" );
}

void iscool::system::haptic_feedback::emit_low_impact( bool keep_prepared )
{
    ic_console_log
        ( "iscool::system", "Haptic feedback 'low impact'." );
     
    if( keep_prepared )
        prepare_low_impact();
}

void iscool::system::haptic_feedback::prepare_medium_impact()
{
    ic_console_log( "iscool::system", "Prepare medium impact haptic feedback" );
}

void iscool::system::haptic_feedback::emit_medium_impact( bool keep_prepared )
{
    ic_console_log
        ( "iscool::system", "Haptic feedback 'medium impact'." );
     
    if( keep_prepared )
        prepare_medium_impact();
}

void iscool::system::haptic_feedback::prepare_heavy_impact()
{
    ic_console_log( "iscool::system", "Prepare heavy impact haptic feedback" );
}

void iscool::system::haptic_feedback::emit_heavy_impact( bool keep_prepared )
{
    ic_console_log
        ( "iscool::system", "Haptic feedback 'heavy impact'." );
     
    if( keep_prepared )
        prepare_heavy_impact();
}

