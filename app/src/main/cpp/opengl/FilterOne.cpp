//
// Created by Administrator on 2021/8/19 0019.
//

#include "FilterOne.h"
#include "../utils/ShaderUtil.h"
#include "../matrix/MatrixUtil.h"

FilterOne::FilterOne() {
    LOGD("FilterOne constructor");
}

FilterOne::~FilterOne() {
    LOGD("FilterOne destructor");
}

void FilterOne::onCreate() {
    LOGD("FilterOne onCreate +");
    vertex = "attribute vec4 v_Position;\n"
             "attribute vec2 f_Position;\n"
             "varying vec2 ft_Position;\n"
             "uniform mat4 u_Matrix;\n"
             "void main() {\n"
             "    ft_Position = f_Position;\n"
             "    gl_Position = v_Position * u_Matrix;\n"
             "}";
    fragment = "precision mediump float;\n"
               "varying vec2 ft_Position;\n"
               "uniform sampler2D sTexture;\n"
               "void main() {\n"
               "    gl_FragColor=texture2D(sTexture, ft_Position);\n"
               "}";

    program = createProgram(vertex, fragment);
    LOGD("opengl program is %d", program);

    vPosition = glGetAttribLocation(program, "v_Position");//顶点坐标
    fPosition = glGetAttribLocation(program, "f_Position");//纹理坐标
    sampler = glGetUniformLocation(program, "sTexture");//2D纹理
    u_matrix = glGetUniformLocation(program, "u_Matrix");

    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   //s=x, t=y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    LOGD("FilterOne onCreate -");
}

void FilterOne::onChange(int width, int height) {
    LOGD("FilterOne onCreate");

    glViewport(0, 0, width, height);
    setMatrix(width, height);
}

void FilterOne::onDraw() {
    LOGD("FilterOne onDraw +");

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glUniformMatrix4fv(u_matrix, 1, GL_FALSE, matrix);

    glActiveTexture(GL_TEXTURE5);
    glUniform1i(sampler, 5);

    glBindTexture(GL_TEXTURE_2D, textureId);

    if(pixels != NULL)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     width_pic, height_pic, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }

    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 8, vertexs);

    glEnableVertexAttribArray(fPosition);
    glVertexAttribPointer(fPosition, 2, GL_FLOAT, false, 8, fragments);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);

    LOGD("FilterOne onDraw -");
}

void FilterOne::setMatrix(int width, int height) {
    LOGD("FilterOne setMatrix + , surface_width:%d, surface_height:%d",width,height);
    initMatrix(matrix);

    float screen_r = 1.0 * width / height;
    float picture_r = 1.0 * width_pic / height_pic;

    if(screen_r > picture_r) //图片宽度缩放
    {
        float r = width / (1.0 * height / height_pic * width_pic);
        orthoM(-r, r, -1, 1, matrix);
    } else{//图片高度缩放
        float r = height / (1.0 * width / width_pic * height_pic);
        orthoM(-1, 1, -r, r, matrix);
    }
}

void FilterOne::setPixelData(void *data, int width_, int height_, int length) {
    LOGD("FilterOne setPixelData +, pic width_:%d, height_:%d",width_,height_);
    width_pic = width_;
    width_pic = height_;
    pixels = data;
    if(surface_height > 0 && surface_width > 0)
    {
        LOGD("FilterOne, surface_width:%d, surface_height:%d",surface_width,surface_height);
        setMatrix(surface_width, surface_height);
    }
    LOGD("FilterOne setPixelData -");
}
