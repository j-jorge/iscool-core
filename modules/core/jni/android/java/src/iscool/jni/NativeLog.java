package iscool.jni;

import iscool.log.LogDelegate;

import java.util.ArrayList;
import java.util.List;

public class NativeLog implements LogDelegate
{
    private class LogEntry
    {
        public int level;
        public String tag;
        public String message;

        public LogEntry( int level, String tag, String message ) {

            this.level = level;
            this.tag = tag;
            this.message = message;
        }
    }
    
    private static final int MAX_QUEUE_SIZE = 1024;
    private List< LogEntry > _queue = new ArrayList();
    
    private static long _nativeDelegate = 0;

    private static NativeLog _instance = new NativeLog();

    public static NativeLog defaultInstance() {
        return _instance;
    }
    
    @Override
    public void writeLog( int level, String tag, String message ) {

        synchronized( this ) {
            
            if ( _nativeDelegate != 0 )
                nativeLog( level, tag, message );
            else {
                if ( _queue.size() + 1 == MAX_QUEUE_SIZE )
                    _queue.remove( 0 );
                
                _queue.add( new LogEntry( level, tag, message ) );
            }
        }
    }

    public static void nativeReady( long nativeDelegate ) {

        _instance.updateNativeReadyState( nativeDelegate );
    }

    private void updateNativeReadyState( long nativeDelegate ) {

        synchronized( this ) {
            _nativeDelegate = nativeDelegate;

            if ( nativeDelegate != 0 ) {
                for ( LogEntry entry : _queue )
                    nativeLog( entry.level, entry.tag, entry.message );

                _queue.clear();
            }
        }
    }

    private static void nativeLog( int level, String tag, String message ) {
        NativeCall.call( _nativeDelegate, level, tag, message );
    }
}
