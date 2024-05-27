package iscool.system;

import androidx.annotation.Keep;

import android.content.Context;
import android.os.Vibrator;
import android.os.VibrationEffect;

@Keep
public class HapticFeedbackService
{
    static private Vibrator _vibrator;
    static private VibrationEffect _clickEffect;

    static void init( Context context ) {
        _vibrator =
            (Vibrator)context.getSystemService(Context.VIBRATOR_SERVICE);
        _clickEffect =
            VibrationEffect.createPredefined(VibrationEffect.EFFECT_CLICK);
    }

    static public void click() {
        if ((_vibrator == null) || (_clickEffect == null))
            return;

        _vibrator.vibrate(_clickEffect);
    }
}
