#include <jni.h>
#include <string>
#include "Egl/egl.h"
#include "GLES2/gl2.h"
#include "android/native_window.h"  //ANativeWindow
#include "android/native_window_jni.h"  //ANativeWindow_fromSurface
#include "EglThread.h"

ANativeWindow  *window = NULL;
EglThread *eglThread = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_peter_openglsample_opengl_NativeOpenGl_surfaceCreate(JNIEnv *env, jobject thiz, jobject surface)
{
    window = ANativeWindow_fromSurface(env,surface);
    eglThread = new  EglThread();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_peter_openglsample_opengl_NativeOpenGl_surfaceChange(JNIEnv *env, jobject thiz, jint width, jint height)
{
}