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
package iscool.social;

import android.content.*;
import android.content.pm.PackageManager;
import android.net.Uri;

import java.io.UnsupportedEncodingException;

public class LinkService
{
    private static Context _context = null;
    
    public static void init( Context context ) {
        assert _context == null;
        assert context != null;
        
        _context = context;
    }

    public static void openInFacebook( byte[] pageBytes ) {

        assert _context != null;
        
        final String page = makeString( pageBytes );

        if ( page == null )
            return;

        openInApp
            ( "com.facebook.katana", "fb://page/" + page,
              "https://www.facebook.com/" + page );
    }

    public static void openInTwitter( byte[] pageBytes ) {

        assert _context != null;
        
        final String page = makeString( pageBytes );

        if ( page == null )
            return;

        openInApp
            ( "com.twitter.android", "twitter://user?screen_name=" + page,
              "https://twitter.com/" + page );
    }
    
    private static String makeString( byte[] bytes ) {

        try {
            return new String( bytes, "UTF-8" );
        } catch( UnsupportedEncodingException e ) {
            e.printStackTrace();
            return null;
        }
    }

    private static void openInApp
        ( String packageName, String appUrl, String fallbackUrl ) {

        String selectedUrl;
        
        if ( applicationIsAvailable( packageName ) )
            selectedUrl = appUrl;
        else
            selectedUrl = fallbackUrl;
        
        final Intent browserIntent =
            new Intent( Intent.ACTION_VIEW, Uri.parse( selectedUrl ) );
        _context.startActivity( browserIntent );
    }

    private static boolean applicationIsAvailable( String packageName ) {

        try {
            _context.getPackageManager().getApplicationInfo( packageName, 0 );
            return true;
        } catch( PackageManager.NameNotFoundException e ) {
            return false;
        }
    }
}
