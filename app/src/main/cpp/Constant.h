//
// Created by huion on 2024/4/8.
//

#ifndef NATIVEGLES_CONSTANT_H
#define NATIVEGLES_CONSTANT_H

class Constant {
public :
    const int RENDERMODE_WHEN_DIRTY = 0;
    const int RENDERMODE_CONTINUOUSLY = 1;
    const int DEBUG_CHECK_GL_ERROR = 1;
    const int DEBUG_LOG_GL_CALLS = 2;

    const bool LOG_ATTACH_DETACH = false;
    const bool LOG_THREADS = false;
    const bool LOG_PAUSE_RESUME = false;
    const bool LOG_SURFACE = false;
    const bool LOG_RENDERER = false;
    const bool LOG_RENDERER_DRAW_FRAME = false;
    const bool LOG_EGL = false;
};

#endif //NATIVEGLES_CONSTANT_H
