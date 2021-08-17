//
// Created by lz6600 on 2021/8/17.
//

#ifndef OPENGLSAMPLE_EGLTHREAD_H
#define OPENGLSAMPLE_EGLTHREAD_H

#include <EGL/eglplatform.h>
#include "pthread.h"

class EglThread
{
public:
    pthread_mutex_t pthread_mutex;
    pthread_cond_t pthread_cond;

public:
    EglThread();

    ~EglThread();

    void onSurfaceCreate(EGLNativeWindowType window);
};


#endif //OPENGLSAMPLE_EGLTHREAD_H
