package iscool.log;

import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.List;

public class Log
{
    private static List<LogDelegate> _delegates = new ArrayList<LogDelegate>();

    public static void registerDelegate( LogDelegate delegate ) {
        _delegates.add( delegate );
    }

    public static void unregisterDelegate( LogDelegate delegate ) {
        _delegates.remove( delegate );
    }
    
    public static void e( String tag, String message, Throwable throwable ) {

        if ( _delegates.isEmpty() )
            android.util.Log.e( tag, message, throwable );
        
        dispatch( android.util.Log.ERROR, tag, message, throwable );
    }

    public static void e( String tag, String message ) {

        if ( _delegates.isEmpty() )
            android.util.Log.e( tag, message );
        
        dispatch( android.util.Log.ERROR, tag, message );
    }

    public static void w( String tag, String message, Throwable throwable ) {

        if ( _delegates.isEmpty() )
            android.util.Log.w( tag, message, throwable );
        
        dispatch( android.util.Log.WARN, tag, message, throwable );
    }

    public static void w( String tag, String message ) {

        if ( _delegates.isEmpty() )
            android.util.Log.w( tag, message );
        
        dispatch( android.util.Log.WARN, tag, message );
    }

    public static void i( String tag, String message, Throwable throwable ) {

        if ( _delegates.isEmpty() )
            android.util.Log.i( tag, message, throwable );
        
        dispatch( android.util.Log.INFO, tag, message, throwable );
    }

    public static void i( String tag, String message ) {

        if ( _delegates.isEmpty() )
            android.util.Log.i( tag, message );
        
        dispatch( android.util.Log.INFO, tag, message );
    }

    public static void d( String tag, String message, Throwable throwable ) {

        if ( _delegates.isEmpty() )
            android.util.Log.d( tag, message, throwable );
        
        dispatch( android.util.Log.DEBUG, tag, message, throwable );
    }

    public static void d( String tag, String message ) {

        if ( _delegates.isEmpty() )
            android.util.Log.d( tag, message );
        
        dispatch( android.util.Log.DEBUG, tag, message );
    }
    
    private static void dispatch( int level, String tag, String message ) {

        for ( LogDelegate delegate : _delegates )
            delegate.writeLog( level, tag, message );
    }

    private static void dispatch
        ( int level, String tag, String message, Throwable throwable ) {

        final StringWriter stringWriter = new StringWriter();
        stringWriter.write(message + '\n');
        
        final PrintWriter printWriter = new PrintWriter( stringWriter );
        throwable.printStackTrace( printWriter );

        dispatch( level, tag, stringWriter.toString() );
    }
    
    native static void nativeLog( int level, String tag, String message );
}
