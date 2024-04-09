//
// Created by huion on 2024/4/8.
//

#include "EglHelper.h"

#include <vector>

#include "Constant.h"
#include "LogUtil.h"
#include "ConfigChooser.h"

void EglHelper::start() {
    mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEglDisplay == EGL_NO_DISPLAY) {
        throwEglException("eglGetDisplay");
    }
    int major;
    int mijor;
    auto rs = eglInitialize(mEglDisplay, &major, &mijor);
    if (!rs) {
        LOGE("EglHelper", "eglInitialize error");
        return;
    }

    if (p_ConfigChooser.use_count() > 0) {
        mEglConfig = p_ConfigChooser->chooseConfig(mEglDisplay);
        std::vector<int> attrib_list;
        attrib_list.push_back(EGL_CONTEXT_CLIENT_VERSION);
        attrib_list.push_back(p_ConfigChooser->attrib.mVersion);
        attrib_list.push_back(EGL_NONE);
        eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, attrib_list.data());
    }
}

bool EglHelper::createSurface() {
    if (mEglDisplay == nullptr || mEglConfig == nullptr || nativeWindow == nullptr) {
        return false;
    }
    destroySurfaceImp();
    mEglSurface = eglCreateWindowSurface(mEglDisplay, mEglConfig, nativeWindow, nullptr);
    if (mEglSurface == nullptr) {
        int error = eglGetError();
        if (error == EGL_BAD_NATIVE_WINDOW) {
            LOGE("EglHelper", "createWindowSurface returned EGL_BAD_NATIVE_WINDOW.");
        }
        return false;
    }
    return true;
}

bool EglHelper::makeCurrent() {
    auto rs = eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext);
    if (!rs) {
        logEglErrorAsWarning("EglHelper", "eglMakeCurrent", eglGetError());
    }
    return rs;
}

bool EglHelper::swap() {
    auto rs = eglSwapBuffers(mEglDisplay, mEglSurface);
    if (!rs) {
        logEglErrorAsWarning("EglHelper", "eglMakeCurrent", eglGetError());
    }
    return rs;
}

void EglHelper::destroySurface() {
    destroySurfaceImp();
}

void EglHelper::finish() {
    auto rs = eglDestroyContext(mEglDisplay, mEglContext);
    mEglContext = nullptr;
    eglTerminate(mEglDisplay);
    mEglDisplay = nullptr;
}

void EglHelper::destroySurfaceImp() {
    if (mEglSurface != nullptr && mEglSurface != EGL_NO_SURFACE) {
        eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE,
                            EGL_NO_SURFACE,
                            EGL_NO_CONTEXT);
        eglDestroySurface(mEglDisplay, mEglSurface);
        mEglSurface = nullptr;
    }
}

void EglHelper::throwEglException(std::string function) {

}

void EglHelper::throwEglException(std::string function, int error) {

}

void EglHelper::logEglErrorAsWarning(std::string tag, std::string function, int error) {

}

void EglHelper::formatEglError(std::string function, int error) {

}

void EglHelper::setPConfigChooser(const std::shared_ptr<ConfigChooser> &configChooser) {
    p_ConfigChooser = configChooser;
}

void EglHelper::setNativeWindow(ANativeWindow *nativeWindow) {
    EglHelper::nativeWindow = nativeWindow;
}
