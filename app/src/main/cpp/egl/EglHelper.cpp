//
// Created by lz6600 on 2021/8/17.
//

#include "EglHelper.h"

//Java
//import javax.microedition.khronos.egl.EGL10;
//import javax.microedition.khronos.egl.EGLConfig;
//import javax.microedition.khronos.egl.EGLContext;
//import javax.microedition.khronos.egl.EGLDisplay;
//import javax.microedition.khronos.egl.EGLSurface;

EglHelper::EglHelper() {
    eglDisplay = EGL_NO_DISPLAY;
    eglSurface = EGL_NO_SURFACE;
    eglContext = EGL_NO_CONTEXT;
    eglConfig = NULL;

}

EglHelper::~EglHelper() {

}

int EglHelper::initEgl(EGLNativeWindowType win) {
//    1、得到默认的显示设备（就是窗口） -- eglGetDisplay
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay error");
        return -1;
    }
//    2、初始化默认显示设备 -- eglInitialize
    EGLint *version = new EGLint[2];
    if (!eglInitialize(eglDisplay, &version[0], &version[1])) {
        LOGE("eglInitialize error");
        return -1;
    }
//    3、设置显示设备的属性
    const EGLint attrib[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8,
            EGL_STENCIL_SIZE, 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE    //TODO must set to end
    };
    EGLint num_config;
    if (!eglChooseConfig(eglDisplay, attrib, NULL, 1, &num_config)) {
        LOGE("eglChooseConfig error 1");
        return -1;
    }
//    4、从系统中获取对应属性的配置 -- eglChooseConfig
    if (!eglChooseConfig(eglDisplay, attrib, &eglConfig, num_config, &num_config)) {
        LOGE("eglChooseConfig error 2");
        return -1;
    }
//    5、创建EglContext -- eglCreateContext
    int attrib_list[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE //TODO must set to end
    };
    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, attrib_list);
    if (eglContext == EGL_NO_CONTEXT) {
        LOGE("eglCreateContext error");
        return -1;
    }
//    6、创建要渲染显示的Surface(window,是ANativeWindow类型) -- eglCreateWindowSurface
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, win, NULL);
    if (eglSurface == EGL_NO_SURFACE) {
        LOGE("eglCreateWindowSurface error");
        return -1;
    }
//    7、绑定EglContext和Surface到显示设备中 -- eglMakeCurrent
    if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
        LOGE("eglMakeCurrent error");
        return -1;
    }

    return 0;
}

int EglHelper::swapBuffers() {
    if (eglDisplay != EGL_NO_DISPLAY && eglSurface != EGL_NO_SURFACE) {
        //    8、刷新数据，显示渲染场景 -- eglSwapBuffers
        //将后端的surface（缓冲）渲染到window中
        if (eglSwapBuffers(eglDisplay, eglSurface)) {
            return 0;
        }
    }
    return -1;
}

void EglHelper::destoryEgl() {

}
