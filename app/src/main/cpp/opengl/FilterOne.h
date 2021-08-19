//
// Created by Administrator on 2021/8/19 0019.
//

#ifndef OPENGLSAMPLE_FILTERONE_H
#define OPENGLSAMPLE_FILTERONE_H

#include "BaseOpenGL.h"

class FilterOne : public BaseOpenGL{
public:
    GLint vPosition;
    GLint fPosition;
    GLint sampler;
    GLuint textureId;
    GLint u_matrix;

    int width_pic;  //设置图片的宽
    int height_pic; //设置图片的高
    void *pixels = NULL;

    float matrix[16];

public:
    FilterOne();

    ~FilterOne();

    void onCreate();

    void onChange(int width, int height);

    void onDraw();

    void setMatrix(int width, int height);

    void setPixelData(void *data, int width, int height, int length);
};


#endif //OPENGLSAMPLE_FILTERONE_H
