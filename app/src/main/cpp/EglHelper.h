//
// Created by huion on 2024/4/8.
//

#ifndef NATIVEGLES_EGLHELPER_H
#define NATIVEGLES_EGLHELPER_H

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <string>
#include <memory>

class ConfigChooser;

class EglHelper {
private:
    EGLDisplay mEglDisplay = nullptr;
    EGLSurface mEglSurface = nullptr;
    EGLConfig mEglConfig = nullptr;
    EGLContext mEglContext = nullptr;

    void destroySurfaceImp();

    void throwEglException(std::string function);

    std::shared_ptr<ConfigChooser> p_ConfigChooser;

    EGLNativeWindowType nativeWindow = nullptr;

public:
    void start();

    bool createSurface();

    bool makeCurrent();

    bool swap();

    void destroySurface();

    void finish();

    static void throwEglException(std::string function, int error);

    static void logEglErrorAsWarning(std::string tag, std::string function, int error);

    static void formatEglError(std::string function,  int error);

    void setPConfigChooser(const std::shared_ptr<ConfigChooser> &configChooser);

    void setNativeWindow(ANativeWindow *nativeWindow);
};


#endif //NATIVEGLES_EGLHELPER_H
