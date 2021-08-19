package com.peter.openglsample.opengl;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

public class MySurfaceView extends SurfaceView implements SurfaceHolder.Callback {
    private NativeOpenGL nativeOpenGl;

    public MySurfaceView(Context context) {
        this(context, null);
    }

    public MySurfaceView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public MySurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        getHolder().addCallback(this);
    }

//    public MySurfaceView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
//        super(context, attrs, defStyleAttr, defStyleRes);
//    }

    public void setNativeOpenGl(NativeOpenGL nativeOpenGl) {
        this.nativeOpenGl = nativeOpenGl;
    }

    private OnSurfaceListener onSurfaceListener;

    public void setOnSurfaceListener(OnSurfaceListener onSurfaceListener) {
        this.onSurfaceListener = onSurfaceListener;
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder surfaceHolder) {
        if (nativeOpenGl != null) {
            nativeOpenGl.surfaceCreate(surfaceHolder.getSurface());

            if(onSurfaceListener != null)
            {
                onSurfaceListener.init();
            }
        }
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder surfaceHolder, int format, int width, int height) {
        if (nativeOpenGl != null) {
            nativeOpenGl.surfaceChange(width, height);
        }
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder surfaceHolder) {
        if (nativeOpenGl != null) {
            nativeOpenGl.surfaceDestroy();
        }
    }

    public interface OnSurfaceListener
    {
        void init();
    }
}
