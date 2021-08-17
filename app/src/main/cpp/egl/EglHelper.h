//
// Created by lz6600 on 2021/8/17.
//

#ifndef OPENGLSAMPLE_EGLHELPER_H
#define OPENGLSAMPLE_EGLHELPER_H

#include "EGL/egl.h"
#include "../utils/AndroidLog.h"

class EglHelper
{
public:
    EGLDisplay eglDisplay;//显示设备
    EGLSurface eglSurface;//后端显示的surface（缓冲）
    EGLConfig eglConfig;//egl配置
    EGLContext eglContext;//egl上下文

public:
    EglHelper();
    ~EglHelper();
    int initEgl(EGLNativeWindowType win);
    int swapBuffers();
    void destoryEgl();
};


#endif //OPENGLSAMPLE_EGLHELPER_H
