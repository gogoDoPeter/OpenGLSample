# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.
project("openglsample")

# 批量导入 源文件
file(GLOB src_files *.cpp)

add_library( # Sets the name of the library.
        native-lib
        # Sets the library as a shared library.
        SHARED

        native-lib.cpp
        egl/EglHelper.cpp
        egl/EglThread.cpp
        opengl/BaseOpenGL.cpp
        opengl/FilterOne.cpp
        opengl/MyOpenGL.cpp
        )

target_link_libraries( # Specifies the target library.
        native-lib
        # Links the target library to the log library
        # included in the NDK.
        log
        EGL
        GLESv2
        android
        )