//
// Created by huion on 2024/4/8.
//

#ifndef NATIVEGLES_CONFIGCHOOSER_H
#define NATIVEGLES_CONFIGCHOOSER_H

#include <EGL/egl.h>

typedef struct {
    int mRedSize = 0;
    int mGreenSize = 0;
    int mBlueSize = 0;
    int mAlphaSize = 0;
    int mDepthSize = 0;
    int mStencilSize = 0;
    int mVersion = 2;
} AttributeList;

class ConfigChooser {
private:
    EGLConfig chooseConfigImp(EGLDisplay& display, const EGLConfig *configs, const int num_configs) const;

public:
    AttributeList attrib;

    EGLConfig chooseConfig(void *&display) const;
};

#endif //NATIVEGLES_CONFIGCHOOSER_H
