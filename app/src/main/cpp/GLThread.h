//
// Created by huion on 2024/4/8.
//

#ifndef NATIVEGLES_GLTHREAD_H
#define NATIVEGLES_GLTHREAD_H

#include <memory>
#include <mutex>
#include <functional>
#include <deque>
#include <condition_variable>
#include <EGL/egl.h>
#include <EGL/eglext.h>

class EglHelper;

using Runnable = std::function<void()>;

class GLThread {
private:
    bool mShouldExit = false;
    bool mRequestPaused = false;
    bool mPaused = false;
    bool mHasSurface = false;
    bool mSurfaceIsBad = false;
    bool mWaitingForSurface = false;
    bool mHaveEglContext = false;
    bool mHaveEglSurface = false;
    bool mFinishedCreatingEglSurface = false;
    bool mShouldReleaseEglContext = false;
    int mWidth = 0;
    int mHeight = 0;
    int mRenderMode = 0;
    bool mRequestRender = false;
    bool mWantRenderNotification = false;
    bool mRenderComplete = false;
    std::deque<Runnable> mEventQueue;
    bool mSizeChanged = true;
    Runnable mFinishDrawingRunnable;
    std::shared_ptr<EglHelper> mEglHelper;
//    WeakReference<? extends  IGLView> mGLSurfaceViewWeakRef;
    //static final GLThreadManager sGLThreadManager = new GLThreadManager();
    std::mutex sGLThreadManager;
    std::condition_variable cv;

    void stopEglSurfaceLocked();

    void stopEglContextLocked();

    void guardedRun();

    bool ableToDraw();

    EGLNativeWindowType nativeWindow = nullptr;

    bool preserveEglContextOnPause = false;

public:
    bool mExited;

    void run();

    void setRenderMode(int renderMode);

    int getRenderMode() const;

    void requestRender();

    void requestRenderAndNotify(const Runnable& finishDrawing);

    void surfaceCreated();

    void surfaceDestroyed();

    void onPause();

    void onResume();

    void onWindowResize(int w, int h);

    void requestExitAndWait();

    void requestReleaseEglContextLocked();

    void queueEvent(const Runnable&  r);
};


#endif //NATIVEGLES_GLTHREAD_H
