//
// Created by huion on 2024/4/8.
//

#include <vector>
#include "ConfigChooser.h"
#include "EglHelper.h"
#include "LogUtil.h"

EGLConfig ConfigChooser::chooseConfig(EGLDisplay &display) const {
    std::vector attrs = {
            EGL_RED_SIZE, attrib.mRedSize,
            EGL_GREEN_SIZE, attrib.mGreenSize,
            EGL_BLUE_SIZE, attrib.mBlueSize,
            EGL_ALPHA_SIZE, attrib.mAlphaSize,
            EGL_DEPTH_SIZE, attrib.mDepthSize,
            EGL_STENCIL_SIZE, attrib.mStencilSize,
            EGL_RENDERABLE_TYPE, attrib.mVersion,
           };

    if (attrib.mVersion == 2) {
        attrs.push_back(EGL_RENDERABLE_TYPE);
        attrs.push_back(EGL_OPENGL_ES2_BIT);
    } else if (attrib.mVersion == 3) {
        attrs.push_back(EGL_RENDERABLE_TYPE);
        attrs.push_back(EGL_OPENGL_ES3_BIT_KHR);
    }

    attrs.push_back(EGL_NONE);
    int num_configs;
    auto rs = eglChooseConfig(display, attrs.data(), nullptr, 0, &num_configs);
    if (!rs || num_configs <= 0) {
        LOGE("ConfigChooser", "eglChooseConfig ERROR");
        return nullptr;
    }
    EGLConfig configs[num_configs];
    rs = eglChooseConfig(display, attrs.data(), configs, num_configs, &num_configs);
    if (!rs) {
        LOGE("ConfigChooser", "eglChooseConfig ERROR");
        return nullptr;
    }
    auto config = chooseConfigImp(display, configs, num_configs);
    return config;
}

EGLConfig ConfigChooser::chooseConfigImp(EGLDisplay& display, const EGLConfig *configs, const int num_configs) const {
    if (num_configs > 0) {
        return configs[0];
    }
    return nullptr;
}
