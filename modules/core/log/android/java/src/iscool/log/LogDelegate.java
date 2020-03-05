package iscool.log;

public interface LogDelegate
{
    void writeLog( int level, String tag, String message );
}
