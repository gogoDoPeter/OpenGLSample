//
// Created by lz6600 on 2021/8/17.
//

#ifndef OPENGLSAMPLE_EGLTHREAD_H
#define OPENGLSAMPLE_EGLTHREAD_H

#include "pthread.h"
#include <unistd.h>
#include <EGL/eglplatform.h>
#include "EglHelper.h"
#include <GLES2/gl2.h>
#include <sys/syscall.h>

#define OPENGL_RENDER_AUTO 1
#define OPENGL_RENDER_HANDLE 2

class EglThread {
public:
    pthread_mutex_t pthread_mutex;
    pthread_cond_t pthread_cond;
    pthread_t pid_egl = -1;
    bool isCreate = false;
    bool isChange = false;
    bool isStart = false;
    bool isExit = false;
    ANativeWindow *nativeWindow = nullptr;
    int render_type = OPENGL_RENDER_AUTO;
    int surfaceWidth;
    int surfaceHeight;

    typedef void (*CallbackOnCreate)(void *);
    CallbackOnCreate onCreate;
    void *onCreateCtx;

    typedef void (*CallbackOnChange)(void *, int width, int height);
    CallbackOnChange onChange;
    void *onChangeCtx;

    typedef void (*CallbackOnDraw)(void *);
    CallbackOnDraw  onDraw;
    void *onDrawCtx;

public:
    EglThread();

    ~EglThread();

    void onSurfaceCreate(EGLNativeWindowType window);

    void setRenderType(int renderType);

    void onSurfaceChange(int width, int height);

    void callbackOnCreate(CallbackOnCreate onCreate, void *ctx);
    void callbackOnChange(CallbackOnChange onChange, void *ctx);
    void callbackOnDraw(CallbackOnDraw  onDraw, void *ctx);

    void notifyRender();

    void destroy();
};


#endif //OPENGLSAMPLE_EGLTHREAD_H
