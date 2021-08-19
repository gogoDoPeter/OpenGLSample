#include <jni.h>
#include <string>
#include "Egl/egl.h"
#include "GLES2/gl2.h"
#include "android/native_window.h"  //ANativeWindow
#include "android/native_window_jni.h"  //ANativeWindow_fromSurface
#include "egl/EglHelper.h"
#include "EglThread.h"
#include "utils/ShaderUtil.h"

const char *vertex = "attribute vec4 v_Position;\n"
                     "attribute vec2 f_Position;\n"
                     "varying vec2 ft_Position;\n"
                     "void main() {\n"
                     "    ft_Position = f_Position;\n"
                     "    gl_Position = v_Position;\n"
                     "}";
const char *fragment = "precision mediump float;\n"
                       "varying vec2 ft_Position;\n"
                       "uniform sampler2D sTexture;\n"
                       "void main() {\n"
                       "    gl_FragColor=texture2D(sTexture, ft_Position);\n"
                       "}";

ANativeWindow *window = NULL;
EglThread *eglThread = NULL;
GLuint program;
GLint vPosition;
GLint fPosition;
GLint sampler;
GLuint textureId;
int width;
int height;
void *pixels = NULL;

float vertexs[] = {
        1, -1,
        1, 1,
        -1, -1,
        -1, 1
};

float fragments[] = {
        1, 1,
        1, 0,
        0, 1,
        0, 0
};

void callback_SurfaceCreate(void *ctx) {
    LOGD("callback_SurfaceCreate current TID: %d, PID: %d", syscall(__NR_gettid),
         syscall(__NR_getpid));
    //1, 加载shader和生成program过程
    program = createProgram(vertex, fragment);
    LOGD("opengl program is %d", program);

    //获取着色器中变量
    vPosition = glGetAttribLocation(program, "v_Position");//顶点坐标
    fPosition = glGetAttribLocation(program, "f_Position");//纹理坐标
    sampler = glGetUniformLocation(program, "sTexture");//2D纹理

    //  2, 创建和绑定纹理：
    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);//绑定纹理
    //  3、设置环绕和过滤方式,
    //  设置初始化必要变量值和相关属性
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (pixels != NULL) {   //4、设置渲染要显示的数据
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }

    glBindTexture(GL_TEXTURE_2D, 0);//解除纹理绑定
}

void callback_SurfaceChange(void *ctx, int w, int h) {
    LOGD("callback_SurfaceChange current TID: %d, PID: %d", syscall(__NR_gettid),
         syscall(__NR_getpid));
    glViewport(0, 0, w, h);
}

//getpid()得到的是进程的pid，在内核中，每个线程都有自己的PID，要得到线程的PID,必须用syscall(SYS_gettid);
void callback_SurfaceDraw(void *ctx) {
    LOGD("callback_SurfaceDraw current TID: %d, PID: %d", syscall(__NR_gettid),
         syscall(__NR_getpid));
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //5, 使用渲染程序
    glUseProgram(program);

    glActiveTexture(GL_TEXTURE5);//默认不设置用GL_TEXTURE0
    glUniform1i(sampler, 5);

    glBindTexture(GL_TEXTURE_2D, textureId);//绑定纹理
    //    6、绑定顶点坐标和纹理坐标
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 8, vertexs);

    glEnableVertexAttribArray(fPosition);
    glVertexAttribPointer(fPosition, 2, GL_FLOAT, false, 8, fragments);

    //    7、绘制图形
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //    8、解除纹理绑定
    glBindTexture(GL_TEXTURE_2D, 0);//解除纹理绑定
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

extern "C"
JNIEXPORT void JNICALL
Java_com_peter_openglsample_opengl_NativeOpenGl_setImgData(JNIEnv *env, jobject thiz, jint width_,
                                                           jint height_, jint length,
                                                           jbyteArray data_) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    width = width_;
    height = height_;
    pixels = malloc(length);
    memcpy(pixels, data, length);
    env->ReleaseByteArrayElements(data_, data, 0);
}