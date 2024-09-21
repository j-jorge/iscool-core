package iscool.system;

import androidx.annotation.Keep;

import android.content.Context;
import android.os.Build;
import android.os.Vibrator;
import android.os.VibrationEffect;

@Keep
public class HapticFeedbackService
{
    static private Vibrator _vibrator = null;
    static private VibrationEffect _clickEffect = null;

    static void init(Context context) {
        _vibrator =
            (Vibrator)context.getSystemService(Context.VIBRATOR_SERVICE);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q)
            _clickEffect =
                VibrationEffect.createPredefined(VibrationEffect.EFFECT_CLICK);
    }

    static public void click() {
        if (_vibrator == null)
            return;

        if (_clickEffect == null) {
            _vibrator.vibrate(20);
            return;
        }

        _vibrator.vibrate(_clickEffect);
    }
}
