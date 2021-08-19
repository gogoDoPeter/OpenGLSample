package com.peter.openglsample;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.os.Process;
import com.peter.openglsample.opengl.MySurfaceView;
import com.peter.openglsample.opengl.NativeOpenGl;

import java.nio.ByteBuffer;

import static android.os.Process.myPid;
import static android.os.Process.myTid;

public class MainActivity extends AppCompatActivity {
    private static final String TAG="opengl_tag_"+MainActivity.class.getSimpleName();
    private MySurfaceView surfaceView;
    private NativeOpenGl nativeOpenGl;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG,"onCreate +");
        super.onCreate(savedInstanceState);
        Log.d(TAG,"onCreate setContentView, myTid = "+myPid()+", Thread id = "+myTid());
        setContentView(R.layout.activity_main);
        Log.d(TAG,"onCreate findViewById");
        surfaceView = ((MySurfaceView) findViewById(R.id.surfaceview));
        Log.d(TAG,"onCreate new NativeOpenGl");
        nativeOpenGl = new NativeOpenGl();
        Log.d(TAG,"onCreate surfaceView.setNativeOpenGl");
        surfaceView.setNativeOpenGl(nativeOpenGl);


        final Bitmap bitmap = BitmapFactory.decodeResource(getResources(),
                R.drawable.milanda2);
        ByteBuffer fcbuffer = ByteBuffer.allocate(bitmap.getHeight() * bitmap.getWidth() * 4);
        bitmap.copyPixelsToBuffer(fcbuffer);
        fcbuffer.flip();
        byte[] pixels = fcbuffer.array();
        nativeOpenGl.setImgData(bitmap.getWidth(), bitmap.getHeight(), pixels.length, pixels);
        Log.d(TAG,"onCreate -");

    }

}