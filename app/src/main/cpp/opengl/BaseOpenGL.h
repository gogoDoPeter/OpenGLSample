//
// Created by Administrator on 2021/8/19 0019.
//

#ifndef OPENGLSAMPLE_BASEOPENGL_H
#define OPENGLSAMPLE_BASEOPENGL_H

#include <cstring>
#include <GLES2/gl2.h>
#include "../utils/AndroidLog.h"

class BaseOpenGL {
public:
    int surface_width;
    int surface_height;

    char * vertex;  //vertex shader source code
    char * fragment;//fragment shader source code

    float *vertexs;
    float *fragments;

    GLuint program;

public:
    BaseOpenGL();
    virtual ~BaseOpenGL();  //Derry tell Base destory func should define virtual

    virtual void onCreate();

    virtual void onChange(int w, int h);

    virtual void onDraw();

    virtual void destroy();

    virtual void setPixelData(void *data, int width, int height, int length);
};


#endif //OPENGLSAMPLE_BASEOPENGL_H
