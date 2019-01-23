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

import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;
import android.os.Build;

import java.util.Calendar;
import java.util.Locale;
import java.util.TimeZone;

public class SystemService
{
    static private Context _context;

    static public void init( Context context ) {
        _context = context;
    }
    
    static public String getLanguageCode() {

        final String language = Locale.getDefault().toString();
        final int separator = language.indexOf( '_' );

        if ( separator == - 1 )
            return language;
        
        return language.substring( 0, separator );
    }

    static public long getDeviceTime() {

        return
            Calendar.getInstance().getTimeInMillis()
            + TimeZone.getDefault().getRawOffset();
    }

    static public void sendToBackground() {

        final Intent intent = new Intent( Intent.ACTION_MAIN );
        intent.addCategory( Intent.CATEGORY_HOME );
        _context.startActivity( intent );
    }

    static public String getApplicationVersion() {

        try {
            final PackageInfo info =
                _context.getPackageManager().getPackageInfo
                ( _context.getPackageName(), 0 );
        
            return info.versionName;
        } catch ( PackageManager.NameNotFoundException e ) {
            return "n/a";
        }
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
        intent.putExtra( Intent.EXTRA_EMAIL, address );
        intent.putExtra( Intent.EXTRA_SUBJECT, subject );
        intent.putExtra( Intent.EXTRA_TEXT, body );

        if ( intent.resolveActivity( _context.getPackageManager() ) != null ) {
            _context.startActivity( intent );
        }
    }
    
}
