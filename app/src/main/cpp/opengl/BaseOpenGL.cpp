//
// Created by Administrator on 2021/8/19 0019.
//

#include "BaseOpenGL.h"


BaseOpenGL::BaseOpenGL() {
    LOGD("BaseOpenGL constructor");
    vertexs = new float[8];
    fragments = new float[8];

    float v[] = {1, -1,
                 1, 1,
                 -1, -1,
                 -1, 1};
    memcpy(vertexs, v, sizeof(v));

    float f[] = {1, 1,
                 1, 0,
                 0, 1,
                 0, 0};
    memcpy(fragments, f, sizeof(f));
}

BaseOpenGL::~BaseOpenGL() {
    LOGD("BaseOpenGL destructor");
    delete []vertexs;
    delete []fragments;
}

void BaseOpenGL::onCreate() {
    LOGD("BaseOpenGL onCreate");
}

void BaseOpenGL::onChange(int w, int h) {
    LOGD("BaseOpenGL onChange");
}

void BaseOpenGL::onDraw() {
    LOGD("BaseOpenGL onDraw");
}

void BaseOpenGL::destroy() {
    LOGD("BaseOpenGL destroy");
}

void BaseOpenGL::setPixelData(void *data, int width, int height, int length) {
    LOGD("BaseOpenGL setPixelData");
}
