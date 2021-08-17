//
// Created by lz6600 on 2021/8/17.
//

#ifndef OPENGLSAMPLE_ANDROIDLOG_H
#define OPENGLSAMPLE_ANDROIDLOG_H

#include "android/log.h"

#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG, "my_tag", FORMAT, ##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "my_tag", FORMAT, ##__VA_ARGS__);


#endif //OPENGLSAMPLE_ANDROIDLOG_H
