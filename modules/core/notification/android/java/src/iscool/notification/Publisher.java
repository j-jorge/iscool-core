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
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.graphics.drawable.BitmapDrawable;
import android.support.v4.app.NotificationCompat;

public class Publisher extends BroadcastReceiver
{
    public static String NOTIFICATION_ID = "notification-id";
    public static String NOTIFICATION_TITLE = "notification-title";
    public static String NOTIFICATION_MESSAGE = "notification-message";
    public static String NOTIFICATION_CHANNEL = "notification-channel";
    public static String NOTIFICATION_SMALL_ICON_NAME =
        "notification-small-icon-name";
    public static String NOTIFICATION_LARGE_ICON_NAME =
        "notification-large-icon-name";
    public static String NOTIFICATION_CONTENT_INTENT =
        "notification-content-intent";

    public void onReceive( Context context, Intent intent ) {

        final int id = intent.getIntExtra( NOTIFICATION_ID, 0 );
        final String title = intent.getStringExtra( NOTIFICATION_TITLE );
        final String message = intent.getStringExtra( NOTIFICATION_MESSAGE );
        final String channel = intent.getStringExtra( NOTIFICATION_CHANNEL );
        final String smallIconName =
            intent.getStringExtra( NOTIFICATION_SMALL_ICON_NAME );
        final String largeIconName =
            intent.getStringExtra( NOTIFICATION_LARGE_ICON_NAME );
        final PendingIntent contentIntent =
            intent.getParcelableExtra( NOTIFICATION_CONTENT_INTENT );

        if ( ( title == null ) || ( message == null ) || ( channel == null )
             || ( smallIconName == null ) || ( largeIconName == null )
             || ( contentIntent == null ) )
            return;
        
        final NotificationCompat.BigTextStyle textStyle =
            new NotificationCompat.BigTextStyle();

        textStyle.setBigContentTitle( title );
        textStyle.bigText( message );

        final Resources resources = context.getResources();
        final String packageName = context.getPackageName();
        final int smallIconId =
            resources.getIdentifier( smallIconName, "drawable", packageName );
        final int largeIconId =
            resources.getIdentifier( largeIconName, "drawable", packageName );
        
        final NotificationCompat.Builder builder =
            new NotificationCompat.Builder( context )
            .setStyle( textStyle )
            .setChannelId( channel )
            .setContentTitle( title )
            .setContentText( message )
            .setContentIntent( contentIntent )
            .setAutoCancel( true )
            .setSmallIcon( smallIconId )
            .setLargeIcon
            ( ( ( BitmapDrawable )resources.getDrawable( largeIconId ) )
              .getBitmap() );
        
        final NotificationManager notificationManager =
            ( NotificationManager ) context.getSystemService
            ( Context.NOTIFICATION_SERVICE );

        notificationManager.notify( id, builder.build() );
    }
}
