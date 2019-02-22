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
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.SystemClock;

class Scheduler {

    private final Activity _activity;
    private final String _smallIcon;
    private final String _largeIcon;
    private final static String _defaultChannelId = "default";
    
    public Scheduler( Activity activity, String smallIcon, String largeIcon ) {

        _activity = activity;
        _smallIcon = smallIcon;
        _largeIcon = largeIcon;

        registerDefaultChannel();
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

        final Intent notificationIntent =
            new Intent( _activity, Publisher.class );
        
        notificationIntent.putExtra
            ( Publisher.NOTIFICATION_ID, intentId );
        notificationIntent.putExtra
            ( Publisher.NOTIFICATION_TITLE, title );
        notificationIntent.putExtra
            ( Publisher.NOTIFICATION_MESSAGE, message );
        notificationIntent.putExtra
            ( Publisher.NOTIFICATION_CHANNEL, _defaultChannelId );
        notificationIntent.putExtra
            ( Publisher.NOTIFICATION_SMALL_ICON_NAME, _smallIcon );
        notificationIntent.putExtra
            ( Publisher.NOTIFICATION_LARGE_ICON_NAME, _largeIcon );
        notificationIntent.putExtra
            ( Publisher.NOTIFICATION_CONTENT_INTENT, createContentIntent() );

        return PendingIntent.getBroadcast
            ( _activity, intentId, notificationIntent,
              PendingIntent.FLAG_CANCEL_CURRENT );
    }

    private PendingIntent createContentIntent() {
        
        final Intent intent = new Intent( _activity, _activity.getClass() );

        intent.setFlags
            ( Intent.FLAG_ACTIVITY_CLEAR_TOP
              | Intent.FLAG_ACTIVITY_SINGLE_TOP );

        return PendingIntent.getActivity( _activity, 0, intent, 0 );
    }

    private void registerDefaultChannel() {

        if ( Build.VERSION.SDK_INT < Build.VERSION_CODES.O ) {
            return;
        }
        
        final CharSequence name =
            _activity.getString( R.string.default_notification_channel_name );
        final int importance = NotificationManager.IMPORTANCE_DEFAULT;
        final NotificationChannel channel =
            new NotificationChannel( _defaultChannelId, name, importance );
        
        final String description =
            _activity.getString
            ( R.string.default_notification_channel_description );
        channel.setDescription( description );

        final NotificationManager notificationManager =
            _activity.getSystemService( NotificationManager.class );
        notificationManager.createNotificationChannel( channel );
    }
}
