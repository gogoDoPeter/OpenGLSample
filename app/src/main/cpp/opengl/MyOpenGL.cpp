//
// Created by Administrator on 2021/8/19 0019.
//

#include "MyOpenGL.h"
#include "FilterOne.h"

void callback_SurfaceCreate(void *ctx) {

    MyOpenGL *wlOpengl = static_cast<MyOpenGL *>(ctx);

    if (wlOpengl != NULL && wlOpengl->baseOpenGl != NULL) {
        wlOpengl->baseOpenGl->onCreate();
    }
}

void callback_SurfaceChange(void *ctx, int width, int height) {
    MyOpenGL *wlOpengl = static_cast<MyOpenGL *>(ctx);
    if (wlOpengl != NULL && wlOpengl->baseOpenGl != NULL) {
        wlOpengl->baseOpenGl->onChange(width, height);
    }
}

void callback_SurfaceDraw(void *ctx) {

    MyOpenGL *wlOpengl = static_cast<MyOpenGL *>(ctx);
    if (wlOpengl != NULL && wlOpengl->baseOpenGl != NULL) {
        wlOpengl->baseOpenGl->onDraw();
    }
}

MyOpenGL::MyOpenGL() {

}

MyOpenGL::~MyOpenGL() {

}

void MyOpenGL::onCreateSurface(JNIEnv *env, jobject surface) {
    nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread = new EglThread();
    eglThread->setRenderType(OPENGL_RENDER_HANDLE);
    eglThread->callbackOnCreate(callback_SurfaceCreate, this);
    eglThread->callbackOnChange(callback_SurfaceChange, this);
    eglThread->callbackOnDraw(callback_SurfaceDraw, this);


    baseOpenGl = new FilterOne();

    eglThread->onSurfaceCreate(nativeWindow);
}

void MyOpenGL::onChangeSurface(int width, int height) {
    if(eglThread != NULL)
    {
        if(baseOpenGl != NULL)
        {
            baseOpenGl->surface_width = width;
            baseOpenGl->surface_height = height;
        }
        eglThread->onSurfaceChange(width, height);
    }
}

void MyOpenGL::onDestorySurface() {
    if(eglThread != NULL)
    {
        eglThread->destroy();
    }
    if(baseOpenGl != NULL)
    {
        baseOpenGl->destroy();
        delete baseOpenGl;
        baseOpenGl = NULL;
    }
    if(nativeWindow != NULL)
    {
        ANativeWindow_release(nativeWindow);
        nativeWindow = NULL;
    }
}

void MyOpenGL::setPixelData(void *data, int width, int height, int length) {
    pic_width = width;
    pic_height = height;
    pixel = malloc(length);     //TODO where to release
    memcpy(pixel, data, length);
    if(baseOpenGl != NULL)
    {
        baseOpenGl->setPixelData(pixel, width, height, length);
    }
    if(eglThread != NULL)
    {
        eglThread->notifyRender();
    }
}
