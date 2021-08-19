//
// Created by Administrator on 2021/8/19 0019.
//

#ifndef OPENGLSAMPLE_SHADERUTIL_H
#define OPENGLSAMPLE_SHADERUTIL_H
#include <GLES2/gl2.h>

static int loadShaders(int shaderType, const char *code)
{
    //1,创建shader（顶点着色器或片元着色器）
    int shader = glCreateShader(shaderType);
    //2,加载shader源码
    glShaderSource(shader, 1, &code, 0);
    //3,编译shader
    glCompileShader(shader);
    return  shader;
}

static GLuint createProgram(const char *vertex , const char * fragment)
{
    //1,加载shader
    int vertexShader = loadShaders(GL_VERTEX_SHADER, vertex);
    int fragmentShader = loadShaders(GL_FRAGMENT_SHADER, fragment);
    //2,创建一个渲染程序
    GLuint program = glCreateProgram();
    //3,将着色器（顶点+片元）程序添加到渲染程序中
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    //4,链接源程序
    glLinkProgram(program);
    return program;
}

#endif //OPENGLSAMPLE_SHADERUTIL_H
