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
#ifndef ISCOOL_SYSTEM_DETAIL_HAPTIC_FEEDBACK_MOCKUP_H
#define ISCOOL_SYSTEM_DETAIL_HAPTIC_FEEDBACK_MOCKUP_H

namespace iscool
{
    namespace system
    {
        enum class haptic_feedback_notification;

        class haptic_feedback
        {
        public:
            bool is_available() const;
            bool is_enabled() const;

            void set_enabled( bool enabled );

            void prepare_notification();
            void emit_notification
            ( haptic_feedback_notification feedback,
              bool keep_prepared = false );

            void prepare_selection();
            void emit_selection( bool keep_prepared = false );

            void prepare_low_impact();
            void emit_low_impact( bool keep_prepared = false );

            void prepare_medium_impact();
            void emit_medium_impact( bool keep_prepared = false );

            void prepare_heavy_impact();
            void emit_heavy_impact( bool keep_prepared = false );
        };
    }
}

#endif
