//
// Created by huion on 2022/9/19.
//

#ifndef NATIVE3DENGINE_LOGUTIL_H
#define NATIVE3DENGINE_LOGUTIL_H

#include <android/log.h>
#include <string>
#include <sstream>

#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGW(TAG, ...) __android_log_print(ANDROID_LOG_WARN,  TAG, __VA_ARGS__)
#define LOGI(TAG, ...) __android_log_print(ANDROID_LOG_INFO,  TAG, __VA_ARGS__)
#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

template <typename T>
std::string VectorToString(const std::vector<T>& myVector) {
    std::stringstream ss;
    for (const auto &element : myVector) {
        ss << element << ", ";
    }
    return ss.str();
}

#endif //NATIVE3DENGINE_LOGUTIL_H
