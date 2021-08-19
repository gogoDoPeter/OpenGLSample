//
// Created by Administrator on 2021/8/19 0019.
//

#ifndef OPENGLSAMPLE_MYOPENGL_H
#define OPENGLSAMPLE_MYOPENGL_H

#include "../egl/EglThread.h"
#include "android/native_window.h"  //ANativeWindow
#include "android/native_window_jni.h"  //ANativeWindow_fromSurface
#include "BaseOpenGL.h"
#include <cstdlib>

class MyOpenGL {
public:
    EglThread *eglThread = NULL;
    ANativeWindow *nativeWindow = NULL;
    BaseOpenGL *baseOpenGl = NULL;

    int pic_width;
    int pic_height;
    void *pixel = NULL;

public:
    MyOpenGL();
    ~MyOpenGL();

    void onCreateSurface(JNIEnv *env, jobject surface);

    void onChangeSurface(int width, int height);

    void onDestorySurface();

    void setPixelData(void *data, int width, int height, int length);
};


#endif //OPENGLSAMPLE_MYOPENGL_H
