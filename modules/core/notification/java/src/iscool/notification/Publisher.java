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

import android.app.Notification;
import android.app.NotificationManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class Publisher extends BroadcastReceiver
{
    public static String NOTIFICATION_ID = "notification-id";
    public static String NOTIFICATION = "notification";

    public void onReceive( Context context, Intent intent ) {

        final NotificationManager notificationManager =
            ( NotificationManager ) context.getSystemService
            ( Context.NOTIFICATION_SERVICE );

        final Notification notification =
            intent.getParcelableExtra( NOTIFICATION );
        final int id = intent.getIntExtra( NOTIFICATION_ID, 0 );
        
        android.util.Log.e( "NOTIF", "notify id=" + id );
        notificationManager.notify( id, notification );
    }
}
