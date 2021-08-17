//
// Created by lz6600 on 2021/8/17.
//

#include "EglThread.h"

EglThread::EglThread()
{
    pthread_mutex_init(&pthread_mutex, NULL);
    pthread_cond_init(&pthread_cond, NULL);
}

EglThread::~EglThread()
{
    pthread_mutex_destroy(&pthread_mutex);
    pthread_cond_destroy(&pthread_cond);
}

void EglThread::onSurfaceCreate(EGLNativeWindowType window)
{

}
