package com.peter.openglsample;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import com.peter.openglsample.opengl.MySurfaceView;
import com.peter.openglsample.opengl.NativeOpenGl;

public class MainActivity extends AppCompatActivity {

    private MySurfaceView surfaceView;
    private NativeOpenGl nativeOpenGl;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        surfaceView = ((MySurfaceView) findViewById(R.id.surfaceview));

        nativeOpenGl = new NativeOpenGl();

        surfaceView.setNativeOpenGl(nativeOpenGl);

    }

}