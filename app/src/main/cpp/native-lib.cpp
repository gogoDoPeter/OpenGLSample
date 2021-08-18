#include <jni.h>
#include <string>
#include "Egl/egl.h"
#include "GLES2/gl2.h"
#include "android/native_window.h"  //ANativeWindow
#include "android/native_window_jni.h"  //ANativeWindow_fromSurface
#include "egl/EglHelper.h"
#include "EglThread.h"

ANativeWindow *window = NULL;
EglThread *eglThread = NULL;

void callback_SurfaceCreate(void *ctx) {
    LOGD("callback_SurfaceCreate current TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));
}

void callback_SurfaceChange(void *ctx, int w, int h) {
    LOGD("callback_SurfaceChange current TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));
    glViewport(0, 0, w, h);
}

//getpid()得到的是进程的pid，在内核中，每个线程都有自己的PID，要得到线程的PID,必须用syscall(SYS_gettid);
void callback_SurfaceDraw(void *ctx) {
    LOGD("callback_SurfaceDraw current TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_peter_openglsample_opengl_NativeOpenGl_surfaceCreate(JNIEnv *env, jobject thiz,
                                                              jobject surface) {
    /**
     * Return the ANativeWindow associated with a Java Surface object,
     * for interacting with it through native code.  This acquires a reference
     * on the ANativeWindow that is returned; be sure to use ANativeWindow_release()
     * when done with it so that it doesn't leak.
     */
    //得到一个和Surface关联的NativeWindow窗口
    window = ANativeWindow_fromSurface(env, surface);

    eglThread = new EglThread();
    eglThread->callbackOnCreate(callback_SurfaceCreate, eglThread);
    eglThread->callbackOnChange(callback_SurfaceChange, eglThread);
    eglThread->callbackOnDraw(callback_SurfaceDraw, eglThread);

    eglThread->setRenderType(OPENGL_RENDER_HANDLE);
    //为什么将nativeWindow传进去，因为创建egl环境需要这个
    LOGD("set window by onSurfaceCreate");
    eglThread->onSurfaceCreate(window);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_peter_openglsample_opengl_NativeOpenGl_surfaceChange(JNIEnv *env, jobject thiz, jint width,
                                                              jint height) {
    LOGD("set size by onSurfaceChange");
    eglThread->onSurfaceChange(width, height);

    usleep(1000000);
    eglThread->notifyRender();
}