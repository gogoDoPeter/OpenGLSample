package com.peter.openglsample.opengl;

import android.view.Surface;

public class NativeOpenGL {


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public native void surfaceCreate(Surface surface) ;

    public native void surfaceChange(int width, int height) ;

    public native void setImgData(int width, int height, int length, byte[] data);

    public native void surfaceDestroy();
}
