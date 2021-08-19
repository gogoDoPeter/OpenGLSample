//
// Created by lz6600 on 2021/8/17.
//

#include "EglThread.h"


EglThread::EglThread() {
    pthread_mutex_init(&pthread_mutex, NULL);
    pthread_cond_init(&pthread_cond, NULL);
}

EglThread::~EglThread() {
    pthread_mutex_destroy(&pthread_mutex);
    pthread_cond_destroy(&pthread_cond);
}

//线程函数，运行在子线程中
void *eglThreadImp(void *context) {
    EglThread *eglThread = static_cast<EglThread *>(context);
    if (eglThread != nullptr) {
        EglHelper *pEglHelper = new EglHelper();

        pEglHelper->initEgl(eglThread->nativeWindow);

        eglThread->isExit = false;
        while (true) {
            //在这里拿到数据，可以渲染到NativeWindow上？ 不可以
            if (eglThread->isCreate) {
                LOGD("eglThread isCreate");
                if (eglThread->onCreate) {
                    LOGD("eglThread  callback eglThread->onCreate");
                    LOGD("eglThread current TID: %d, PID: %d", syscall(__NR_gettid),
                         syscall(__NR_getpid));
                    eglThread->onCreate(eglThread->onCreateCtx);
                }
                eglThread->isCreate = false;
            }
            if (eglThread->isChange) {
                LOGD("eglThread  isChange");
                eglThread->isChange = false;
                if (eglThread->onChange) {
                    LOGD("eglThread  callback eglThread->onChange");
                    LOGD("eglThread current TID: %d, PID: %d", syscall(__NR_gettid),
                         syscall(__NR_getpid));
                    eglThread->onChange(eglThread->onChangeCtx, eglThread->surfaceWidth,
                                        eglThread->surfaceHeight);
                    eglThread->isStart = true;
                }

            }
            if (eglThread->isStart) {
                if (eglThread->onDraw) {
                    LOGD("eglThread  callback eglThread->onDraw");
//                    LOGD("eglThread current TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));
                    eglThread->onDraw(eglThread->onDrawCtx);
                }
                //将缓存surface的数据渲染到window上
                pEglHelper->swapBuffers();
            }
            if (eglThread->render_type == OPENGL_RENDER_AUTO) {
                usleep(1000000 / 60); //单位：微妙
            }else{
                pthread_mutex_lock(&eglThread->pthread_mutex);
                pthread_cond_wait(&eglThread->pthread_cond,&eglThread->pthread_mutex);
                pthread_mutex_unlock(&eglThread->pthread_mutex);
            }
            if (eglThread->isExit) {
                pEglHelper->destoryEgl();
                delete pEglHelper;
                pEglHelper = NULL;
                break;
            }
        }
    }
//    pthread_exit(&wlEglThread->eglThread);
    return nullptr;//TODO must do
}

void EglThread::onSurfaceCreate(EGLNativeWindowType window) {
    if (pid_egl == -1) {
        isCreate = true;
        /* TODO why EGLNativeWindowType == ANativeWindow
         typedef struct ANativeWindow*  EGLNativeWindowType;*/
        nativeWindow = window;
        LOGD("create eglThread, isCreate=%d", isCreate);
        pthread_create(&pid_egl, nullptr, eglThreadImp, this);
    }
}

void EglThread::setRenderType(int renderType) {
    this->render_type = renderType;

}

void EglThread::onSurfaceChange(int width, int height) {
    isChange = true;
    surfaceWidth = width;
    surfaceHeight = height;
    LOGD("width=%d, height=%d", surfaceWidth, surfaceHeight);
}

void EglThread::callbackOnCreate(CallbackOnCreate onCreate, void *ctx) {
    LOGD("set onCreate");
    this->onCreate = onCreate;
    this->onCreateCtx = ctx;
}

void EglThread::callbackOnChange(CallbackOnChange onChange, void *ctx) {
    this->onChange = onChange;
    this->onChangeCtx = ctx;
}

void EglThread::callbackOnDraw(CallbackOnDraw onDraw, void *ctx) {
    this->onDraw = onDraw;
    this->onDrawCtx = ctx;
}

void EglThread::notifyRender() {
    pthread_mutex_lock(&pthread_mutex);
    pthread_cond_signal(&pthread_cond);
    pthread_mutex_unlock(&pthread_mutex);
}

void EglThread::destroy() {
    isExit = true;
    notifyRender();
    pthread_join(pid_egl, NULL);
    nativeWindow = NULL;
    pid_egl = -1;
}

