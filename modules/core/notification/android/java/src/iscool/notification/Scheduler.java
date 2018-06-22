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
import android.app.AlarmManager;
import android.app.Notification;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.drawable.BitmapDrawable;
import android.os.SystemClock;
import android.support.v4.app.NotificationCompat;

class Scheduler {

    private final Activity _activity;
    private final int _smallIcon;
    private final int _largeIcon;
    
    public Scheduler( Activity activity, int smallIcon, int largeIcon ) {

        _activity = activity;
        _smallIcon = smallIcon;
        _largeIcon = largeIcon;
    }

    public void schedule
        ( int intentId, long delayInSeconds, String title, String message ) {

        final PendingIntent pendingIntent =
            buildIntent( title, message, intentId );

        final long displayDateMs =
            SystemClock.elapsedRealtime() + delayInSeconds * 1000;
        
        final AlarmManager alarmManager =
            ( AlarmManager ) _activity.getSystemService
            ( Context.ALARM_SERVICE );
        
        alarmManager.set
            ( AlarmManager.ELAPSED_REALTIME_WAKEUP, displayDateMs,
              pendingIntent );
     }

    private PendingIntent buildIntent
        ( String title, String message, int intentId ) {

        final Notification notification = buildNotification( title, message );

        final Intent notificationIntent =
            new Intent( _activity, Publisher.class );
        
        notificationIntent.putExtra
            ( Publisher.NOTIFICATION_ID, intentId );
        notificationIntent.putExtra( Publisher.NOTIFICATION, notification );

        return PendingIntent.getBroadcast
            ( _activity, intentId, notificationIntent,
              PendingIntent.FLAG_CANCEL_CURRENT );
    }
    
    private Notification buildNotification( String title, String message ) {

        NotificationCompat.BigTextStyle textStyle =
            new NotificationCompat.BigTextStyle();

        textStyle.setBigContentTitle( title );
        textStyle.bigText( message );

        final NotificationCompat.Builder builder =
            new NotificationCompat.Builder( _activity )
            .setStyle( textStyle )
            .setContentTitle( title )
            .setContentText( message )
            .setContentIntent( createContentIntent() )
            .setAutoCancel( true )
            .setSmallIcon( _smallIcon )
            .setLargeIcon
            ( ( ( BitmapDrawable )
                _activity.getResources().getDrawable( _largeIcon ) )
              .getBitmap() );

        return builder.build();
    }

    private PendingIntent createContentIntent() {
        
        final Intent intent = new Intent( _activity, _activity.getClass() );

        intent.setFlags
            ( Intent.FLAG_ACTIVITY_CLEAR_TOP
              | Intent.FLAG_ACTIVITY_SINGLE_TOP );

        return PendingIntent.getActivity( _activity, 0, intent, 0 );
    }
}
