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
package iscool.system;

import androidx.annotation.Keep;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.view.WindowManager;

import java.util.Calendar;
import java.util.Locale;
import java.util.TimeZone;

@Keep
public class SystemService
{
    static private Activity _activity;

    static public void init( Activity activity ) {
        _activity = activity;

        HapticFeedbackService.init(activity);
    }

    static public String getLanguageCode() {

        final String language = Locale.getDefault().toString();
        final int separator = language.indexOf( '_' );

        if ( separator == - 1 )
            return language;

        return language.substring( 0, separator );
    }

    static public long getDeviceTime() {

        final TimeZone timeZone = TimeZone.getDefault();

        return
            Calendar.getInstance().getTimeInMillis()
            + timeZone.getRawOffset()
            + timeZone.getDSTSavings();
    }

    static public void keepScreenOn(boolean keepOn) {
        final Runnable setFlag =
            new Runnable() {
                @Override
                public void run() {

                    if (keepOn)
                        _activity.getWindow()
                            .addFlags
                            (WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
                    else
                        _activity.getWindow()
                            .clearFlags
                            (WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
                }
            };

        new Handler(Looper.getMainLooper()).post(setFlag);
    }

    static public void sendToBackground() {

        final Intent intent = new Intent( Intent.ACTION_MAIN );
        intent.addCategory( Intent.CATEGORY_HOME );
        _activity.startActivity( intent );
    }

    static public String getApplicationVersion() {

        try {
            final PackageInfo info =
                _activity.getPackageManager().getPackageInfo
                ( _activity.getPackageName(), 0 );

            return info.versionName;
        } catch ( PackageManager.NameNotFoundException e ) {
            return "n/a";
        }
    }

    static public String getApplicationId() {

        return _activity.getPackageName();
    }

    static public String getOSVersion() {

        return Build.VERSION.RELEASE;
    }

    static public String getDeviceModel() {

        return Build.MODEL;
    }

    static public void sendMail( String address, String subject, String body ) {

        final Intent intent = new Intent( Intent.ACTION_SENDTO );
        intent.setType("text/plain");
        intent.setData( Uri.parse( "mailto:" ) );
        intent.putExtra( Intent.EXTRA_EMAIL, new String[]{ address } );
        intent.putExtra( Intent.EXTRA_SUBJECT, subject );
        intent.putExtra( Intent.EXTRA_TEXT, body );

        if ( intent.resolveActivity( _activity.getPackageManager() ) != null ) {
            _activity.startActivity( intent );
        }
    }

}
