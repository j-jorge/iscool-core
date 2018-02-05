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
import android.net.Uri;
import android.support.v4.content.FileProvider;

import java.io.*;

public class ShareService
{
    private static Context _context = null;
    private static String _fileProviderAuthority = null;
    
    public static void init( Context context, String fileProviderAuthority ) {
        assert _context == null;
        assert context != null;
        
        _context = context;

        assert _fileProviderAuthority == null;
        assert fileProviderAuthority != null;
        
        _fileProviderAuthority = fileProviderAuthority;
    }

    public static void shareMessage( byte[] message ) {

        assert _context != null;

        final Intent shareIntent = createShareIntent( message );

        if ( shareIntent == null )
            return;
        
        shareIntent.setType( "text/plain" );
        _context.startActivity( Intent.createChooser( shareIntent, null ) );
    }

    public static void shareFile( String filePath, byte[] message ) {

        assert _context != null;
        
        final Intent shareIntent = createShareIntent( message );

        if ( shareIntent == null )
            return;

        shareIntent.setType( deduceIntentType( filePath ) );
        shareIntent.addFlags( Intent.FLAG_GRANT_READ_URI_PERMISSION );

        final File file = new File( filePath );
        final Uri uri =
            FileProvider.getUriForFile
            ( _context, _fileProviderAuthority, file );

        shareIntent.putExtra( Intent.EXTRA_STREAM, uri );
        _context.startActivity( Intent.createChooser( shareIntent, null ) );
    }

    private static Intent createShareIntent( byte[] message ) {

        final Intent result = new Intent();

        try {
            result.putExtra
                ( Intent.EXTRA_TEXT, new String( message, "UTF-8" ) );
        } catch( UnsupportedEncodingException e ) {
            e.printStackTrace();
            return null;
        }

        result.setAction( Intent.ACTION_SEND );

        return result;
    }
    
    private static String deduceIntentType( String filePath ) {
        String dotSplit[] = filePath.split("\\.");
        String extension = dotSplit[ dotSplit.length - 1 ];

        if( extension.equals( "png" ) )
            return "image/png";

        if( extension.equals( "jpg" ) )
            return "image/jpeg";

        if( extension.equals( "csv" ) )
            return "text/plain";

        return "text/plain";
    }
}
