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
package iscool.notification;

import android.app.Activity;
import androidx.core.app.NotificationManagerCompat;

public final class NotificationService {

    private static Activity _activity;
    private static Scheduler _scheduler;
    
    public static void init
        ( Activity activity, String smallIcon, String largeIcon ) {

        assert _activity == null;
        assert activity != null;
        assert _scheduler == null;
        
        _activity = activity;
        _scheduler = new Scheduler( activity, smallIcon, largeIcon );
        
        cancelAll();
    }

    public static boolean areNotificationsEnabled() {
        assert _activity != null;

        return NotificationManagerCompat
                .from( _activity )
                .areNotificationsEnabled();
    }

    public static void cancelAll() {
        assert _activity != null;

        NotificationManagerCompat
            .from( _activity )
            .cancelAll();
    }

    public static void schedule
        ( int id, long delayInSeconds, String title, String body ) {

        _scheduler.schedule( id, delayInSeconds, title, body );
    }
    
    private NotificationService() {
        
    }

}
